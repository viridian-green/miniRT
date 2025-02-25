/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:05:07 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/25 16:13:52 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *scene)
{
	(*scene).canvas_height = HEIGHT;
	(*scene).canvas_width = WIDTH;
	scene->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!scene->mlx_ptr)
		free_exit("Error initializing mlx.", scene, 1);
	scene->img = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
	if (!scene->img || \
		mlx_image_to_window((scene)->mlx_ptr, (scene)->img, 0, 0))
		free_exit("Error initializing mlx image.", scene, 1);
}
