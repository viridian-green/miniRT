/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/05 15:39:08 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(double p_x, double p_y, t_vector vp, t_scene *scene)
{
	t_ray		ray;
	t_vector	p_center;
	t_vector	p_x_sc;
	t_vector	p_y_sc;

	p_x_sc = vc_multiply(scene->vp.pixel_x, p_x);
	p_y_sc = vc_multiply(scene->vp.pixel_y, p_y);
	p_center = vc_add(vc_add(scene->vp.pixel_init, p_x_sc), p_y_sc);
	ray.origin = vp;
	ray.direction = vc_subtract(p_center, vp);
	return (ray);
}



