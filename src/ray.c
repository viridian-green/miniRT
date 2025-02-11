/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/11 12:35:47 by ademarti         ###   ########.fr       */
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
/*
int ray_intersects_sp(t_ray ray, t_object object, double *t)
{
    t_vector oc = vc_subtract(ray.origin, object.sp.center);  // Vector from ray origin to sphere center
    double a = vec_dot(ray.direction, ray.direction);  // Dot product of ray direction with itself
    half_b = vec_dot(oc, ray->direction);  // Dot product of ray direction and oc
    double c = vec_dot(oc, oc) - (object.sp.diameter * object.sp.diameter);  // (oc . oc) - r^2
    double discriminant = b * b - 4.0 * a * c;  // Calculate discriminant

    if (discriminant < 0.0)
        return 0;  // No intersection, return false

    // Calculate the entry and exit distances
    *t = (-b - sqrt(discriminant)) / (2.0 * a);  // Entry point
    if (*t >= 0.0)
        return 1;  // Intersection occurs at the entry point

    *t = (-b + sqrt(discriminant)) / (2.0 * a);  // Exit point
    if (*t >= 0.0)
        return 1;  // Intersection occurs at the exit point

    return 0;  // No valid intersection
}
    */
   double	ray_intersects_sp(t_object object, t_ray *ray)
   {
       t_vector	oc;
       double	a;
       double	half_b;
       double	c;
       double	discriminant;

       oc = vc_subtract(ray->origin, object.sp.center);
       a = vec_dot(ray->direction, ray->direction);
       half_b = vec_dot(oc, ray->direction);
       c = vec_dot(oc, oc) - object.sp.diameter * object.sp.diameter / 4;
       discriminant = half_b * half_b - a * c;
       if (discriminant < 0)
       {
           return (-1.0);
       }
       else
       {
           return ((-half_b - sqrt(discriminant)) / a);
       }
   }

int ray_intersects_plane(t_ray ray, t_object object, double *t)
{
    t_vector normal = normalize(object.pl.orientation);
    double denom = vec_dot(ray.direction, normal);

    if (fabs(denom) > 1e-6)
    {
        t_vector oc = vc_subtract(ray.origin, object.pl.plane_point);
        *t = -vec_dot(oc, normal) / denom;

        if (*t > 1e-4)
        {
            return 1;
        }
    }

    return 0;
}
/*

int ray_intersects_plane(t_ray ray, t_object object, double *t)
{
    // Plane normal vector
    t_vector normal = object.pl.orientation;
    // Dot product of ray direction and plane normal
    double denom = vec_dot(ray.direction, normal);

    // Check if ray is parallel to the plane
    if (fabs(denom) > 1e-6)  // A small threshold to avoid floating-point issues
    {
        // Compute the t value
        t_vector oc = vc_subtract(ray.origin, object.pl.plane_point);
        *t = -vec_dot(oc, normal) / denom;

        // Check if intersection is in the positive direction
        if (*t >= 0.0)
            return 1;  // Intersection occurs
    }

    return 0;  // No intersection
}
*/
int ray_intersects_cylinder(t_ray ray, t_object object, double *t)
{
    t_vector oc = vc_subtract(ray.origin, object.cy.center);  // Vector from ray origin to cylinder center
    t_vector direction = ray.direction;
    t_vector axis = object.cy.orientation;
    double r = object.cy.diameter / 2.0;  // Radius of the cylinder

    // Project the ray direction and the center-origin vector onto the cylinder's axis
    double dot_dir_axis = vec_dot(direction, axis);
    double dot_oc_axis = vec_dot(oc, axis);

    // We now form the quadratic equation to solve for intersection t
    t_vector oc_perp = vc_subtract(oc, vc_mult_scalar(axis, dot_oc_axis));  // Vector perpendicular to axis
    t_vector dir_perp = vc_subtract(direction, vc_mult_scalar(axis, dot_dir_axis));  // Ray direction perpendicular to axis

    double a = vec_dot(dir_perp, dir_perp);  // Coefficient for quadratic equation
    double b = 2.0 * vec_dot(oc_perp, dir_perp);
    double c = vec_dot(oc_perp, oc_perp) - r * r;

    // Calculate discriminant
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
        double height1 = vec_dot(vc_subtract(intersection1, object.cy.center), axis);
        if (height1 >= 0.0 && height1 <= object.cy.height)
        {
            *t = t1;
            return 1;
        }
    }

    if (t2 >= 0.0)
    {
        t_vector intersection2 = vc_add(ray.origin, vc_mult_scalar(ray.direction, t2));
        double height2 = vec_dot(vc_subtract(intersection2, object.cy.center), axis);
        if (height2 >= 0.0 && height2 <= object.cy.height)
        {
            *t = t2;
            return 1;
        }
    }

    return 0;  // No valid intersection within the cylinder
}