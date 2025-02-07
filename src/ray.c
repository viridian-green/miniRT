/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/07 15:33:48 by ademarti         ###   ########.fr       */
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

bool intersect_sphere(t_ray ray, t_object object, double *t_out)
{
    t_vector oc = vc_subtract(ray.origin, sphere.center);
    double a = vc_dot(ray.direction, ray.direction); // Assuming direction is normalized, a = 1
    double b = 2.0 * vc_dot(oc, ray.direction);
    double c = vc_dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false; // No intersection
	else
	{
        double sqrt_disc = sqrt(discriminant);
        double t1 = (-b - sqrt_disc) / (2 * a);
        double t2 = (-b + sqrt_disc) / (2 * a);

        if (t1 > 0.001) {  // Small epsilon to avoid floating-point errors
            *t_out = t1;
            return true;  // Intersection at t1 (closest hit)
        } else if (t2 > 0.001) {
            *t_out = t2;
            return true;  // Intersection at t2 (if ray started inside sphere)
        }
        return false; // Both intersections are behind the ray
    }
}



