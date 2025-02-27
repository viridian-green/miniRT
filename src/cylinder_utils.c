/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:20:03 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/27 15:23:59 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	is_cap_or_side_closer(t_results *r, t_object *object, \
	double *t, t_scene *s)
{
	if (r->closest_side >= 0.0 && (r->closest_cap < 0.0 || \
		r->closest_side < r->closest_cap))
	{
		*t = r->closest_side;
		s->intersec.t = *t;
		s->intersec.point = vectorize_t(s->ray, *t);
		r->center_to_point = vc_subtract(s->intersec.point, object->cy.center);
		r->projected = vc_subtract(r->center_to_point, \
			vc_mult_scalar(r->axis, vc_dot(r->center_to_point, r->axis)));
		s->intersec.normal = vc_normalize(r->projected);
		s->intersec.color = object->cy.color;
	}
	else if (r->closest_cap >= 0.0)
	{
		*t = r->closest_cap;
		s->intersec.t = *t;
		s->intersec.point = vectorize_t(s->ray, *t);
		s->intersec.normal = r->axis;
		if (vc_dot(s->ray.direction, r->axis) > 0.0)
			s->intersec.normal = vc_mult_scalar(r->axis, -1.0);
		s->intersec.color = object->cy.color;
	}
}

void	find_t1(t_results *r, t_ray ray, t_object object)
{
	t_vector	intersection1;
	double		height1;

	r->sqrt_discriminant = sqrt(r->discriminant);
	r->t1 = (-r->b - r->sqrt_discriminant) / (2.0 * r->a);
	if (r->t1 >= 0.0)
	{
		intersection1 = vc_add(ray.origin, \
			vc_mult_scalar(ray.direction, r->t1));
		height1 = vc_dot(vc_subtract(intersection1, \
			object.cy.center), r->axis);
		if (height1 >= -object.cy.height / 2.0 \
			&& height1 <= object.cy.height / 2.0)
			r->closest_side = r->t1;
	}
}

void	find_t2(t_results *r, t_ray ray, t_object object, double t_cylinder)
{
	t_vector	intersection2;
	double		height2;

	r->t2 = (-r->b + r->sqrt_discriminant) / (2.0 * r->a);
	if (r->t2 >= 0.0)
	{
		intersection2 = vc_add(ray.origin, \
			vc_mult_scalar(ray.direction, r->t2));
		height2 = vc_dot(vc_subtract(intersection2, \
			object.cy.center), r->axis);
		if (height2 >= -object.cy.height / 2.0 \
			&& height2 <= object.cy.height / 2.0)
			if (t_cylinder < 0.0 || r->t2 < t_cylinder)
				r->closest_side = r->t2;
	}
}

double	find_discriminant(t_results *r, t_ray ray, t_object object)
{
	double	dot_dir_axis;
	double	dot_oc_axis;

	r->oc = vc_subtract(ray.origin, object.cy.center);
	r->axis = vc_normalize(object.cy.orientation);
	dot_dir_axis = vc_dot(ray.direction, r->axis);
	dot_oc_axis = vc_dot(r->oc, r->axis);
	r->top_cap = vc_add(object.cy.center, \
		vc_mult_scalar(r->axis, object.cy.height / 2.0));
	r->oc_perp = vc_subtract(r->oc, vc_mult_scalar(r->axis, dot_oc_axis));
	r->dir_perp = vc_subtract(ray.direction, \
		vc_mult_scalar(r->axis, dot_dir_axis));
	r->radius = object.cy.diameter / 2.0;
	r->a = vc_dot(r->dir_perp, r->dir_perp);
	r->b = 2.0 * vc_dot(r->oc_perp, r->dir_perp);
	r->c = vc_dot(r->oc_perp, r->oc_perp) - r->radius * r->radius;
	return (r->b * r->b - 4.0 * r->a * r->c);
}

/*
In this function we loop through the top and bottom caps.
For each cap, we compute the intersection with the ray
and store it in t_cap.
*/
void	intersections_caps(t_results *r, t_ray ray, t_object object)
{
	t_vector	p;
	double		intersect_cap;
	int			i;

	r->bottom_cap = vc_subtract(object.cy.center, \
		vc_mult_scalar(r->axis, object.cy.height / 2.0));
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			r->curr_cap = r->bottom_cap;
		else
			r->curr_cap = r->top_cap;
		intersect_cap = vc_dot(vc_subtract(r->curr_cap, ray.origin), \
		r->axis) / vc_dot(ray.direction, r->axis);
		if (intersect_cap >= 0.0)
		{
			p = vc_add(ray.origin, \
				vc_mult_scalar(ray.direction, intersect_cap));
			if (vc_length(vc_subtract(p, r->curr_cap)) <= r->radius)
				if (r->closest_cap < 0.0 || intersect_cap < r->closest_cap)
					r->closest_cap = intersect_cap;
		}
		i++;
	}
}
