/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/07 16:06:56 by ademarti         ###   ########.fr       */
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

double	calculate_discriminant(double a, double b, double c)
{
	double	discriminant;

	discriminant = (b * b) - (4.0 * a * c);
	return (discriminant);
}

double	calculate_entry_distance(double a, double b, double discriminant)
{
	double	t1;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	return (t1);
}

double	calculate_exit_distance(double a, double b, double discriminant)
{
	double	t2;

	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (t2);
}

int	ray_intersect_sphere(t_vector ray, t_object object, double *t)
{
	double	b;
	double	discriminant;

	b = 2.0 * vec3_dot(sphere->ixd.oc, ray_dir);
	discriminant = calculate_discriminant(1.0, b, sphere->ixd.c);
	if (discriminant < 0.0)
		return (0);
	*t = calculate_entry_distance(1.0, b, discriminant);
	if (*t >= 0.0)
		return (1);
	*t = calculate_exit_distance(1.0, b, discriminant);
	if (*t >= 0.0)
		return (1);
	return (0);
}



