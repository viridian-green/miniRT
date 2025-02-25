/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:35:20 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/25 15:44:00 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_color(char **line, t_color *color)
{
	int	r;
	int	g;
	int	b;

	split_int(&line[0], &r, &g, &b);
	color->r = r;
	color->g = g;
	color->b = b;
}

t_color	color_init(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int	convert_color(t_color color)
{
	int	rgb;
	int	opacity;

	opacity = 255;
	rgb = (color.r << 24) + (color.g << 16) + (color.b << 8) + opacity;
	return (rgb);
}

void	put_color_pixel(double p_x, double p_y, t_scene *scene, t_ray ray)
{
	int			color;
	t_color		rgb;

	find_nearest_intersection(ray, scene);
	if (scene->intersec.self)
		rgb = light_calc(scene);
	else
		rgb = scene->ambience.color;
	color = convert_color(rgb);
	mlx_put_pixel(scene->img, p_x, p_y, color);
}
