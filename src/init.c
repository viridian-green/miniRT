/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:05:07 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/05 15:55:17 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ambience(t_ambience *ambience)
{
	ambience->light_ratio = 0;
	ambience->color.r = 0;
	ambience->color.g = 0;
	ambience->color.b = 0;
}

void	init_camera(t_camera *camera)
{
	camera->viewpoint.x = 0;
	camera->viewpoint.y = 0;
	camera->viewpoint.z = 0;
	camera->forward_v.x = 0;
	camera->forward_v.y = 0;
	camera->forward_v.z = 0;
	camera->right_v.x = 0;
	camera->right_v.y = 0;
	camera->right_v.z = 0;
	camera->up_v.x = 0;
	camera->up_v.y = 0;
	camera->up_v.z = 0;
	camera->fov = 0;
}

void	init_light(t_light *light)
{
	light->light_point.x = 0;
	light->light_point.y = 0;
	light->light_point.z = 0;
	light->ratio = 0;
	light->color.r = 0;
	light->color.g = 0;
	light->color.b = 0;
}

//not sure if it is correct
//We only need to init the objects
void	init_scene(t_scene *scene)
{
	// t_object *new_object = malloc(sizeof(t_object));
	// if (!new_object)
	// return; // Handle allocation failure

	// init_object(new_object);
	// new_object->next = scene->objects;
	// scene->objects = new_object;
}

void	init_mlx(t_scene *scene)
{
	scene->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!scene->mlx_ptr)
		free_exit("Error initializing mlx.", scene);
	scene->img = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
	if (!scene->img)
		free_exit("Error initializing mlx image.", scene);
}
