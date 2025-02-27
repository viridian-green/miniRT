/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/27 17:31:07 by ademarti         ###   ########.fr       */
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

void	ray_intersects_sp(t_ray ray, t_object object, double *t, t_scene *s)
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
		return ;
	else
	{
		*t = ((-half_b - sqrt(discriminant)) / a);
		s->intersec.t = *t;
		s->intersec.point = vectorize_t(ray, *t);
		s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, \
														object.sp.center));
		s->intersec.color = object.sp.color;
	}
}

void	ray_intersects_pl(t_ray ray, t_object object, double *t, t_scene *s)
{
	t_vector	oc;
	t_vector	normal;
	double		denom;

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
		}
	}
}

void	ray_intersects_cy(t_ray ray, t_object object, double *t, t_scene *s)
{
	t_results	r;

	r.discriminant = find_discriminant(&r, ray, object);
	r.closest_side = -1.0;
	r.closest_cap = -1.0;
	if (r.discriminant >= 0.0)
	{
		find_t1(&r, ray, object);
		find_t2(&r, ray, object, r.closest_side);
	}
	intersections_caps(&r, ray, object);
	s->ray = ray;
	is_cap_or_side_closer(&r, &object, t, s);
}
