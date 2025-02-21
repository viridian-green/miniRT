/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:09:24 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:58 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_add(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

t_color	color_mult(t_color color, double ratio)
{
	t_color	result;

	result.r = color.r * ratio;
	result.g = color.g * ratio;
	result.b = color.b * ratio;
	return (result);
}

t_color	color_init(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	find_diffuse_color(t_scene *scene)
{
	t_ray		l_ray;
	t_color		color;
	double		light_intensity;

	color = color_init(0, 0, 0);
	if (scene->intersec.self && scene->light.ratio)
	{
		l_ray.direction = normalize(vc_subtract(scene->light.light_point, \
												scene->intersec.point));
		l_ray.origin = scene->light.light_point;
		light_intensity = fmax(vec_dot(scene->intersec.normal, \
										l_ray.direction), 0);
		if (!check_shadow(scene, l_ray, scene->intersec) && light_intensity > 0)
			color = color_add(color, color_mult(color_mult(scene->light.color, \
										light_intensity), scene->light.ratio));
	}
	return (color);
}

t_color	light_calc(t_scene *scene)
{
	t_color	amb_color;
	t_color	diff_color;
	t_color	final_color;
	t_color	intersec_color;

	intersec_color = scene->intersec.color;
	amb_color = color_mult(scene->ambience.color, scene->ambience.light_ratio);
	diff_color = find_diffuse_color(scene);
	final_color.r = fmin(fmax(((amb_color.r + diff_color.r) / 255.0) * \
								intersec_color.r, 0), 255.0);
	final_color.g = fmin(fmax(((amb_color.g + diff_color.g) / 255.0) * \
								intersec_color.g, 0), 255.0);
	final_color.b = fmin(fmax(((amb_color.b + diff_color.b) / 255.0) * \
								intersec_color.b, 0), 255.0);
	return (final_color);
}
