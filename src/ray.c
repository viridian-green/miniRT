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


int ray_intersects_cy(t_ray ray, t_object object, double *t, t_scene *s)
{
    t_vector oc = vc_subtract(ray.origin, object.cy.center);  // Vector from ray origin to cylinder center
    t_vector direction = ray.direction;
    t_vector axis = object.cy.orientation;
    double r = object.cy.diameter / 2.0;  // Radius of the cylinder
    double dot_dir_axis = vc_dot(direction, axis);
    double dot_oc_axis = vc_dot(oc, axis);

    // We now form the quadratic equation to solve for intersection t
    t_vector oc_perp = vc_subtract(oc, vc_mult_scalar(axis, dot_oc_axis));  // Vector perpendicular to axis
    t_vector dir_perp = vc_subtract(direction, vc_mult_scalar(axis, dot_dir_axis));  // Ray direction perpendicular to axis

    double a = vc_dot(dir_perp, dir_perp);  // Coefficient for quadratic equation
    double b = 2.0 * vc_dot(oc_perp, dir_perp);
    double c = vc_dot(oc_perp, oc_perp) - r * r;

    (void)s;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return 0;  // No intersection
    // Calculate t values for the intersection
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);

    // Check if any of the t values are valid
    if (t1 >= 0.0)
    {
        // Now, we need to check if the intersection is within the cylinder's height
        t_vector intersection1 = vc_add(ray.origin, vc_mult_scalar(ray.direction, t1));
        double height1 = vc_dot(vc_subtract(intersection1, object.cy.center), axis);
        if (height1 >= 0.0 && height1 <= object.cy.height)
        {
            *t = t1;
			s->intersec.t = *t;
			s->intersec.point = vectorize_t(ray, *t);
			s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object.sp.center));
			s->intersec.color = object.cy.color;
            return 1;
        }
    }
    if (t2 >= 0.0)
    {
        t_vector intersection2 = vc_add(ray.origin, vc_mult_scalar(ray.direction, t2));
        double height2 = vc_dot(vc_subtract(intersection2, object.cy.center), axis);
        if (height2 >= 0.0 && height2 <= object.cy.height)
        {
            *t = t2;
			s->intersec.t = *t;
			s->intersec.point = vectorize_t(ray, *t);
			s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object.sp.center));
			s->intersec.color = object.cy.color;
            return 1;
        }
    }
    return 0;  // No valid intersection within the cylinder
}