/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 14:26:28 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void init_ambience(t_ambient *ambient)
{
	ambient->light_ratio = 0;
	ambient->color.r = 0;
	ambient->color.g = 0;
	ambient->color.b = 0;
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

void init_scene(t_scene *scene)
{
	init_ambience(&scene->ambient);
	init_camera(&scene->camera);
	// init_light();
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
