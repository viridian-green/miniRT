/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/26 17:01:36 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
In this function the pixels are scaled both vertically and horizontally
The variable p_center (pixel center) marks the exact spot on the window in 
3D space for a given pixel (from 2D to 3D)
*/
t_ray	create_ray(double p_x, double p_y, t_vector origin, t_scene *scene)
{
	t_ray		ray;
	t_vector	p_center;
	t_vector	p_x_sc;
	t_vector	p_y_sc;

	p_x_sc = vc_mult_scalar(scene->vp.pixel_x, p_x);
	p_y_sc = vc_mult_scalar(scene->vp.pixel_y, p_y);
	p_center = vc_add(vc_add(scene->vp.pixel_init, p_x_sc), p_y_sc);
	ray.origin = origin;
	ray.direction = vc_subtract(p_center, origin);
	return (ray);
}

double	ray_intersects_sp(t_ray ray, t_object object, double *t, t_scene *s)
{
	t_vector	oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;

	oc = vc_subtract(ray.origin, object.sp.center);
	a = vc_dot(ray.direction, ray.direction);
	half_b = vc_dot(oc, ray.direction);
	c = vc_dot(oc, oc) - object.sp.diameter * object.sp.diameter / 4;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	else
	{
		*t = ((-half_b - sqrt(discriminant)) / a);
		s->intersec.t = *t;
		s->intersec.point = vectorize_t(ray, *t);
		s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, \
														object.sp.center));
		s->intersec.color = object.sp.color;
	}
	return (1);
}

int	ray_intersects_pl(t_ray ray, t_object object, double *t, t_scene *s)
{
	t_vector	normal;
	double		denom;
	t_vector	oc;

	normal = object.pl.orientation;
	denom = vc_dot(ray.direction, normal);
	if (fabs(denom) > 1e-6)
	{
		oc = vc_subtract(ray.origin, object.pl.plane_point);
		*t = -vc_dot(oc, normal) / denom;
		if (*t >= 0.0)
		{
			s->intersec.t = *t;
			s->intersec.point = vectorize_t(ray, *t);
			if (vc_dot(ray.direction, normal) > 0)
				s->intersec.normal = vc_mult_scalar(normal, -1);
			else
				s->intersec.normal = normal;
			s->intersec.color = object.pl.color;
			return (1);
		}
	}
	return (0);
}

static t_vector	compute_oc_perp(t_ray ray, t_object object, t_vector axis)
{
	t_vector	oc;

	oc = vc_subtract(ray.origin, object.cy.center);
	return (vc_subtract(oc, vc_mult_scalar(axis, vc_dot(oc, axis))));
}

static t_vector	compute_dir_perp(t_ray ray, t_vector axis)
{
	return (vc_subtract(ray.direction, vc_mult_scalar(axis, \
		vc_dot(ray.direction, axis))));
}

static int	in_cylinder_height_range(t_vector p, t_object object, t_vector axis)
{
	double	proj;

	proj = vc_dot(vc_subtract(p, object.cy.center), axis);
	return (proj >= -object.cy.height / 2.0 && proj <= object.cy.height / 2.0);
}

static int	solve_quadratic(double A, double B, double C, double t[2])
{
	double	discriminant;

	discriminant = B * B - 4.0 * A * C;
	if (discriminant < 0.0)
		return (0);
	t[0] = (-B - sqrt(discriminant)) / (2.0 * A);
	t[1] = (-B + sqrt(discriminant)) / (2.0 * A);
	return (1);
}

static double	inter_cy_side(t_ray ray, t_object object, t_vector axis, double r)
{
	t_vector	oc_perp;
	t_vector	dir_perp;
	double		roots[2];
	double		t_side;

	oc_perp = compute_oc_perp(ray, object, axis);
	dir_perp = compute_dir_perp(ray, axis);
	t_side = -1.0;
	if (!solve_quadratic(vc_dot(dir_perp, dir_perp),
			(2.0 * vc_dot(oc_perp, dir_perp)),
			(vc_dot(oc_perp, oc_perp) - r * r), roots))
		return (-1.0);
	if (roots[0] >= 0.0 && in_cylinder_height_range(vc_add(ray.origin, \
		vc_mult_scalar(ray.direction, roots[0])), object, axis))
		t_side = roots[0];
	if (roots[1] >= 0.0 && in_cylinder_height_range(vc_add(ray.origin, \
		vc_mult_scalar(ray.direction, roots[1])), object, axis) \
		&& (t_side < 0.0 || roots[1] < t_side))
		t_side = roots[1];
	return (t_side);
}

static double	inter_cy_bottom_cap(t_ray ray, t_object ob, t_vector axis, double r)
{
	double		t_plane;
	t_vector	cap_c;
	t_vector	p;

	cap_c = vc_subtract(ob.cy.center, vc_mult_scalar(axis, ob.cy.height / 2.0));
	t_plane = vc_dot(vc_subtract(cap_c, ray.origin), axis) / \
								vc_dot(ray.direction, axis);
	if (t_plane >= 0.0)
	{
		p = vc_add(ray.origin, vc_mult_scalar(ray.direction, t_plane));
		if (vc_length(vc_subtract(p, cap_c)) <= r)
			return (t_plane);
	}
	return (-1.0);
}

static double	inter_cy_top_cap(t_ray ray, t_object ob, t_vector axis, double r)
{
	double		t_plane;
	t_vector	cap_c;
	t_vector	p;

	cap_c = vc_add(ob.cy.center, vc_mult_scalar(axis, ob.cy.height / 2.0));
	t_plane = vc_dot(vc_subtract(cap_c, ray.origin), axis) / \
								vc_dot(ray.direction, axis);
	if (t_plane >= 0.0)
	{
		p = vc_add(ray.origin, vc_mult_scalar(ray.direction, t_plane));
		if (vc_length(vc_subtract(p, cap_c)) <= r)
			return (t_plane);
	}
	return (-1.0);
}

static double	inter_cy_cap(t_ray ray, t_object ob, t_vector axis, double r)
{
	double	t_bottom;
	double	t_top;

	t_bottom = inter_cy_bottom_cap(ray, ob, axis, r);
	t_top = inter_cy_top_cap(ray, ob, axis, r);
	if (t_bottom >= 0.0 && t_top >= 0.0)
	{
		if (t_bottom < t_top)
			return (t_bottom);
		else
			return (t_top);
	}
	else if (t_bottom >= 0.0)
		return (t_bottom);
	else
		return (t_top);
}

static void	set_cylinder_intersection(t_scene *s, t_ray ray, t_object ob, double t)
{
	s->intersec.t = t;
	s->intersec.point = vectorize_t(ray, t);
	s->intersec.color = ob.cy.color;
}

static t_vector	calc_side_normal(t_ray ray, t_object ob, double t, t_vector axis)
{
	t_vector	center_to_point;

	center_to_point = vc_subtract(vectorize_t(ray, t), ob.cy.center);
	return (vc_normalize(vc_subtract(center_to_point,
				vc_mult_scalar(axis, vc_dot(center_to_point, axis)))));
}

int	ray_intersects_cy(t_ray ray, t_object ob, double *t, t_scene *s)
{
	t_vector	axis;
	double		t_side;
	double		t_cap;

	axis = vc_normalize(ob.cy.orientation);
	t_side = inter_cy_side(ray, ob, axis, ob.cy.diameter / 2.0);
	t_cap = inter_cy_cap(ray, ob, axis, ob.cy.diameter / 2.0);
	if (t_side >= 0.0 && (t_cap < 0.0 || t_side < t_cap))
	{
		*t = t_side;
		s->intersec.normal = calc_side_normal(ray, ob, *t, axis);
	}
	else if (t_cap >= 0.0)
	{
		*t = t_cap;
		if (vc_dot(ray.direction, axis) > 0.0)
			s->intersec.normal = vc_mult_scalar(axis, -1.0);
		else
			s->intersec.normal = axis;
	}
	else
		return (0);
	set_cylinder_intersection(s, ray, ob, *t);
	return (1);
}
