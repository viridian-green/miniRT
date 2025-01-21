/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 16:04:56 by mrabelo-         ###   ########.fr       */
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

	t_point	light_point;
	int		diameter;
	t_color	color;

void init_light(t_light *light)
{
	light->diameter = 0;
	light->color.r = 0;
	light->color.r = 0;
	light->color.r = 0;
}

void init_scene(t_scene *scene)
{
	init_ambience(&scene->ambient);
	init_camera(&scene->camera);
	//init_light();
	// init_objects();
}

void	init_mlx(t_scene *scene)
{
	scene->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!scene->mlx_ptr)
		cleanup(/*scene*/);
	scene->img = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
	if (!scene->img)
		cleanup(/*scene*/);
}

void cleanup(void/*t_scene *scene*/)
{
	//free(scene->mlx_ptr);
	//free(scene->img);
	//free(scene);
	exit(1);
}

void	key_board(mlx_key_data_t key, t_scene *scene)
{
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		mlx_close_window(scene->mlx_ptr);
		return ;
	}
}

int main(int ac, char **av)
{
	t_scene *scene;

	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	scene = ft_calloc(0, sizeof(t_scene));
	if (!scene)
		cleanup();
	init_mlx(scene);
	init_scene(scene);
	parsing(av[1], scene);
	mlx_key_hook(scene->mlx_ptr, (t_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
