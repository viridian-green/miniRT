		/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/22 17:50:52 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/*In this function the pixels are scaled both vertically and horizontally
The variable p_center (pixel center) marks the exact spot on the window in 3D space for a given pixel (from 2D to 3D)
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
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

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
		s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object.sp.center));
		s->intersec.color = object.sp.color;
	}
	return (1);
}

int ray_intersects_pl(t_ray ray, t_object object, double *t, t_scene *s)
{
    // The plane's normal is its orientation
    t_vector normal = object.pl.orientation;

    // Calculate the denominator (dot product between ray direction and plane normal)
    double denom = vc_dot(ray.direction, normal);

    if (fabs(denom) > 1e-6)  // Avoid division by zero
    {
        // Vector from ray origin to a point on the plane
        t_vector oc = vc_subtract(ray.origin, object.pl.plane_point);

        // Calculate the intersection point distance
        *t = -vc_dot(oc, normal) / denom;

        if (*t >= 0.0)  // Check if intersection is in front of the ray
        {
            s->intersec.t = *t;
            s->intersec.point = vectorize_t(ray, *t);  // Compute intersection point
            s->intersec.normal = normal;;  // Plane normal (already normalized)
            s->intersec.color = object.pl.color;  // Store color
            return 1;  // Ray intersects the plane
        }
    }
    return 0;  // No intersection
}

// int ray_intersects_cy(t_ray ray, t_object object, double *t, t_scene *s)
// {
//     t_vector oc = vc_subtract(ray.origin, object.cy.center);  // Vector from ray origin to cylinder center
//     t_vector direction = ray.direction;
//     t_vector axis = object.cy.orientation;
//     double r = object.cy.diameter / 2.0;  // Radius of the cylinder
//     double dot_dir_axis = vc_dot(direction, axis);
//     double dot_oc_axis = vc_dot(oc, axis);

//     // We now form the quadratic equation to solve for intersection t
//     t_vector oc_perp = vc_subtract(oc, vc_mult_scalar(axis, dot_oc_axis));  // Vector perpendicular to axis
//     t_vector dir_perp = vc_subtract(direction, vc_mult_scalar(axis, dot_dir_axis));  // Ray direction perpendicular to axis

//     double a = vc_dot(dir_perp, dir_perp);  // Coefficient for quadratic equation
//     double b = 2.0 * vc_dot(oc_perp, dir_perp);
//     double c = vc_dot(oc_perp, oc_perp) - r * r;

//     (void)s;
//     double discriminant = b * b - 4.0 * a * c;
//     if (discriminant < 0.0)
//         return 0;  // No intersection
//     // Calculate t values for the intersection
//     double sqrt_discriminant = sqrt(discriminant);
//     double t1 = (-b - sqrt_discriminant) / (2.0 * a);
//     double t2 = (-b + sqrt_discriminant) / (2.0 * a);

//     // Check if any of the t values are valid
//     if (t1 >= 0.0)
//     {
//         // Now, we need to check if the intersection is within the cylinder's height
//         t_vector intersection1 = vc_add(ray.origin, vc_mult_scalar(ray.direction, t1));
//         double height1 = vc_dot(vc_subtract(intersection1, object.cy.center), axis);
//         if (height1 >= 0.0 && height1 <= object.cy.height)
//         {
//             *t = t1;
// 			s->intersec.t = *t;
// 			s->intersec.point = vectorize_t(ray, *t);
// 			s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object.cy.center));
// 			s->intersec.color = object.cy.color;
//             return 1;
//         }
//     }
//     if (t2 >= 0.0)
//     {
//         t_vector intersection2 = vc_add(ray.origin, vc_mult_scalar(ray.direction, t2));
//         double height2 = vc_dot(vc_subtract(intersection2, object.cy.center), axis);
//         if (height2 >= 0.0 && height2 <= object.cy.height)
//         {
//             *t = t2;
// 			s->intersec.t = *t;
// 			s->intersec.point = vectorize_t(ray, *t);
// 			s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object.cy.center));
// 			s->intersec.color = object.cy.color;
//             return 1;
//         }
//     }
//     return 0;  // No valid intersection within the cylinder
// }

typedef struct s_roots {
	double	r1;
	double	r2;
}	t_roots;


t_roots	solve_cyl_quadratic(t_ray ray, t_object object, t_vector oc)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_roots	r;

	a = vc_dot(ray.direction, ray.direction) - square(vc_dot(ray.direction, object.cy.orientation));
	half_b = vc_dot(ray.direction, oc) - vc_dot(ray.direction, object.cy.orientation)
		* vc_dot(oc, object.cy.orientation);
	c = vc_dot(oc, oc) - square(vc_dot(oc, object.cy.orientation))
		- object.cy.diameter * object.cy.diameter / 4;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		r.r1 = -1.0;
		r.r2 = -1.0;
		return (r);
	}
	else
	{
		r.r1 = (-half_b - sqrt(discriminant)) / a;
		r.r2 = (-half_b + sqrt(discriminant)) / a;
		return (r);
	}
}

double	hit_cyl_tube(t_ray ray, t_object object)
{
	t_vector	oc;
	t_roots	r;
	double	m1;
	double	m2;

	oc = vc_subtract(ray.origin, object.cy.center);
	r = solve_cyl_quadratic(ray, object, oc);
	if (r.r1 < 0.0 && r.r2 < 0.0)
		return (-1.0);
	m1 = vc_dot(ray.direction, object.cy.orientation) * r.r1 + vc_dot(oc, object.cy.orientation);
	m2 = vc_dot(ray.direction, object.cy.orientation) * r.r2 + vc_dot(oc, object.cy.orientation);
	if ((m1 >= object.cy.height / -2 && m1 <= object.cy.height / 2))
		return (ft_min_double(r.r1, r.r2));
	else if (m2 >= object.cy.height / -2 && m2 <= object.cy.height / 2)
		return (r.r2);
	else
		return (-1.0);
}

// double	hit_cyl_cap(t_o_cy *cyl, t_ray *ray, enum e_hit_part side)
// {
// 	double	t;
// 	double	pc_len;

// 	if (side == TOP)
// 	{
// 		t = hit_plane(cyl->top_plane, ray, NULL);
// 		pc_len = vec_len(vec_sub(point_on_ray(ray, t), cyl->top_plane->pos));
// 		if (t > 0.0 && pc_len <= cyl->diameter / 2)
// 			return (t);
// 		else
// 			return (-1.0);
// 	}
// 	else if (side == BOTTOM)
// 	{
// 		t = hit_plane(cyl->bottom_plane, ray, NULL);
// 		pc_len = vec_len(vec_sub(point_on_ray(ray, t), cyl->bottom_plane->pos));
// 		if (t > 0.0 && pc_len <= cyl->diameter / 2)
// 			return (t);
// 		else
// 			return (-1.0);
// 	}
// 	else
// 		return (-1.0);
// }

int	ray_intersects_cy(t_ray ray, t_object object, double *t, t_scene *s)
{
	double	t_tube;
	double	t_top;
	double	t_bottom;
	double	t;

	t_tube = hit_cyl_tube(ray, object);
	// t_top = hit_cyl_cap(cyl, ray, TOP);
	// t_bottom = hit_cyl_cap(cyl, ray, BOTTOM);
	// t = smallest_positive(3, t_tube, t_top, t_bottom);
	// if (t > 0.0)
	// {
	// 	if (hit_obj)
	// 		**hit_obj = (t_object *)cyl;
	// 	if (t == t_tube)
	// 		cyl->hit_part = TUBE;
	// 	else if (t == t_top)
	// 		cyl->hit_part = TOP;
	// 	else
	// 		cyl->hit_part = BOTTOM;
	// }
	// else
	// 	cyl->hit_part = NONE;
	// return (t);
    return 0;
}