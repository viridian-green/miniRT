/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 16:10:44 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void init_ambience(t_ambience *ambience)
{
	ambience->light_ratio = 0;
	ambience->color.r = 0;
	ambience->color.g = 0;
	ambience->color.b = 0;
}

void init_camera(t_camera *camera)
{
	camera->viewpoint.x = 0;
	camera->viewpoint.y = 0;
	camera->viewpoint.z = 0;
	camera->orientation.x = 0;
	camera->orientation.y = 0;
	camera->orientation.z = 0;
}

	t_point	light_point;
	int		diameter;
	t_color	color;

void init_light(t_light *light)
{
	light->diameter = 0;
	light->color.r = 0;
	light->color.g = 0;
	light->color.b = 0;
}

void init_scene(t_scene *scene)
{
	init_ambience(&scene->ambience);
	init_camera(&scene->camera);
	init_light(&scene->light);
	// init_objects();
}

int main(int ac, char **av)
{
	t_scene *scene;
	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	//init_mlx(scene);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return 1;
	init_scene(scene);
	parsing(av[1], scene);
}
