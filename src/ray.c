/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/07 16:50:50 by ademarti         ###   ########.fr       */
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

	p_x_sc = vc_multiply(scene->vp.pixel_x, p_x);
	p_y_sc = vc_multiply(scene->vp.pixel_y, p_y);
	p_center = vc_add(vc_add(scene->vp.pixel_init, p_x_sc), p_y_sc);
	ray.origin = origin;
	ray.direction = vc_subtract(p_center, origin);
	return (ray);
}

int ray_intersects_sp(t_ray ray, t_object object, double *t)
{
    t_vector oc = vc_subtract(ray.origin, object.sp.center);  // Vector from ray origin to sphere center
    double a = vec3_dot(ray.direction, ray.direction);  // Dot product of ray direction with itself
    double b = 2.0 * vec3_dot(ray.direction, oc);  // Dot product of ray direction and oc
    double c = vec3_dot(oc, oc) - (object.sp.diameter * object.sp.diameter);  // (oc . oc) - r^2
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