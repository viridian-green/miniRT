/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/07 12:32:22 by ademarti         ###   ########.fr       */
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



