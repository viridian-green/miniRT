/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:05:07 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/07 15:32:37 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *scene)
{
	(*scene).canvas_height = HEIGHT;
	(*scene).canvas_width = WIDTH;
	scene->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!scene->mlx_ptr)
		free_exit("Error initializing mlx.", scene);
	scene->img = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
	if (!scene->img)
		free_exit("Error initializing mlx image.", scene);
}
