/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/27 14:27:53 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
In this function the pixels are scaled both vertically and horizontally
The variable p_center (pixel center) marks the exact spot on the window in
3D space for a given pixel (from 2D to 3D)
*/

void is_cap_or_side_closer(t_results r, t_object *object,  double *t,  t_scene *s, t_ray ray)
{
	t_vector axis = vc_normalize(object->cy.orientation);
	if (r.t_side >= 0.0 && (r.closest_cap < 0.0 || r.t_side < r.closest_cap))
    {
		*t = r.t_side;
        s->intersec.t = *t;
        s->intersec.point = vectorize_t(ray, *t);
        {
			t_vector center_to_point = vc_subtract(s->intersec.point, object->cy.center);
            t_vector projected = vc_subtract(center_to_point, vc_mult_scalar(axis, vc_dot(center_to_point, axis)));
            s->intersec.normal = vc_normalize(projected);
        }
        s->intersec.color = object->cy.color;
    }
    else if (r.closest_cap >= 0.0)
    {
		*t = r.closest_cap;
        s->intersec.t = *t;
        s->intersec.point = vectorize_t(ray, *t);
        s->intersec.normal = axis;
        if (vc_dot(ray.direction, axis) > 0.0)
			s->intersec.normal = vc_mult_scalar(axis, -1.0); // Flip normal if hitting from inside
        s->intersec.color = object->cy.color;
    }
}

void find_t1(t_results *r, t_ray ray, t_object object)
{
	t_vector intersection1;
	double height1;

	r->sqrt_discriminant = sqrt(r->discriminant);
	t_vector axis = vc_normalize(object.cy.orientation);
    r->t1 = (-r->b - r->sqrt_discriminant) / (2.0 * r->a);
    if (r->t1 >= 0.0)
    {
        intersection1 = vc_add(ray.origin, vc_mult_scalar(ray.direction, r->t1));
        height1 = vc_dot(vc_subtract(intersection1, object.cy.center), axis);
        if (height1 >= -object.cy.height / 2.0 && height1 <= object.cy.height / 2.0)
            r->t_side = r->t1;
    }
}
void find_t2(t_results *r, t_ray ray, t_object object, double t_cylinder)
{
	t_vector axis;
	t_vector intersection2;
	double height2;

	axis = vc_normalize(object.cy.orientation);
    r->t2 = (-r->b + r->sqrt_discriminant) / (2.0 * r->a);
    if (r->t2 >= 0.0)
    {
        intersection2 = vc_add(ray.origin, vc_mult_scalar(ray.direction, r->t2));
        height2 = vc_dot(vc_subtract(intersection2, object.cy.center), axis);
        if (height2 >= -object.cy.height / 2.0 && height2 <= object.cy.height / 2.0)
            if (t_cylinder < 0.0 || r->t2 < t_cylinder)
				r->t_side = r->t2;
    }
}

void quadratic_equation_coefs(t_results *r, t_object object)
{
	r->radius = object.cy.diameter / 2.0;
	r->a = vc_dot(r->dir_perp, r->dir_perp);
	r->b = 2.0 * vc_dot(r->oc_perp, r->dir_perp);
	r->c = vc_dot(r->oc_perp,r->oc_perp) - r->radius * r->radius;
}
double find_discriminant(t_results *r, t_ray ray, t_object object)
{
	double	dot_dir_axis;
	double	dot_oc_axis;

	r->oc = vc_subtract(ray.origin, object.cy.center);
	r->axis = vc_normalize(object.cy.orientation);
	dot_dir_axis = vc_dot(ray.direction, r->axis);
	dot_oc_axis = vc_dot(r->oc, r->axis);
	r->top_cap = vc_add(object.cy.center, vc_mult_scalar(r->axis, object.cy.height / 2.0));
	r->oc_perp = vc_subtract(r->oc, vc_mult_scalar(r->axis, dot_oc_axis));
	r->dir_perp = vc_subtract(ray.direction, vc_mult_scalar(r->axis, dot_dir_axis));
	quadratic_equation_coefs(r, object);
	return (r->b * r->b - 4.0 * r->a * r->c);
}
/*
In this function we loop through the top and bottom caps.
For each cap, we compute the intersection with the cap's plane.
*/
void	intersections_caps(t_results *r, t_ray ray, t_object object)
{
	t_vector p;
	int	i;

	r->bottom_cap = vc_subtract(object.cy.center, vc_mult_scalar(r->axis, object.cy.height / 2.0));
	r->radius =object.cy.diameter / 2.0;
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			r->curr_cap = r->bottom_cap;
		else
		{
			r->curr_cap = r->top_cap;
        	r->t_plane = vc_dot(vc_subtract(r->curr_cap, ray.origin), r->axis) / vc_dot(ray.direction, r->axis);
		}
		if (r->t_plane >= 0.0)
		{
			p = vc_add(ray.origin, vc_mult_scalar(ray.direction, r->t_plane));
			if (vc_length(vc_subtract(p, r->curr_cap)) <= r->radius)
				if (r->closest_cap < 0.0 || r->t_plane < r->closest_cap)
					r->closest_cap = r->t_plane;
		}
		i++;
	}
}

int ray_intersects_cy(t_ray ray, t_object object, double *t, t_scene *s)
{
	t_results	r = {0};

    r.discriminant = find_discriminant(&r, ray , object);
    r.t_side = -1.0;
	r.closest_cap = -1.0;
    if (r.discriminant >= 0.0)
	{
    	find_t1(&r, ray, object);
    	find_t2(&r, ray, object, r.t_side);
	}
	intersections_caps(&r, ray, object);
	is_cap_or_side_closer(r, &object, t, s, ray);
    return 0;
}
