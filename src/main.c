/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/07 15:38:41 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	key_board(mlx_key_data_t key, t_scene *scene)
{
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		mlx_close_window(scene->mlx_ptr);
		return ;
	}
	//translation(key, scene);
	//rotation(key, scene);
	//zoom(key, scene);
	//update(scene);
}

void	render_image(t_scene *scene)
{
	double		pixel_x;
	double		pixel_y;
	t_ray		ray;

	pixel_x = 0;
	while (pixel_x < scene->canvas_width)
	{
		pixel_y = 0;
		while (pixel_y < scene->canvas_height)
		{
			ray = create_ray(pixel_x, pixel_y, scene->camera.origin, scene);
			put_color_pixel(pixel_x, pixel_y, scene, ray);
			pixel_y++;
		}
		pixel_x++;
	}
}

int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2)
		perror("Error. Please enter the config file as argument.");
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		free_exit("Memory allocation error.", scene);
	init_mlx(scene);
	parsing(av[1], scene);
	printf("ambience color r: %d\n", scene->ambience.color.r);
	printf("ambience color g: %d\n", scene->ambience.color.g);
	printf("ambience color b: %d\n", scene->ambience.color.b);
	printf("ambience light ratio: %f\n", scene->ambience.light_ratio);
	printf("camera origin x: %f\n", scene->camera.origin.x);
	printf("camera origin y: %f\n", scene->camera.origin.y);
	printf("camera origin z: %f\n", scene->camera.origin.z);
	printf("camera forward_v x: %f\n", scene->camera.forward_v.x);
	printf("camera forward_v y: %f\n", scene->camera.forward_v.y);
	printf("camera forward_v z: %f\n", scene->camera.forward_v.z);
	printf("camera right_v x: %f\n", scene->camera.right_v.x);
	printf("camera right_v y: %f\n", scene->camera.right_v.y);
	printf("camera right_v z: %f\n", scene->camera.right_v.z);
	printf("camera up_v x: %f\n", scene->camera.up_v.x);
	printf("camera up_v y: %f\n", scene->camera.up_v.y);
	printf("camera up_v z: %f\n", scene->camera.up_v.z);
	printf("camera fov: %d\n", scene->camera.fov);
	printf("light point x: %f\n", scene->light.light_point.x);
	printf("light point y: %f\n", scene->light.light_point.y);
	printf("light point z: %f\n", scene->light.light_point.z);
	printf("light ratio: %f\n", scene->light.ratio);
	printf("light color r: %d\n", scene->light.color.r);
	printf("light color g: %d\n", scene->light.color.g);
	printf("light color b: %d\n", scene->light.color.b);
	printf("canvas width: %f\n", scene->canvas_width);
	printf("canvas height: %f\n", scene->canvas_height);
	t_object	*current = scene->objects;
	while (current)
	{
		printf("Object type: %d\n", current->type);
		if (current->type == 1)
		{
			printf("Sphere center x: %f\n", current->sp.center.x);
			printf("Sphere center y: %f\n", current->sp.center.y);
			printf("Sphere center z: %f\n", current->sp.center.z);
			printf("Sphere diameter: %f\n", current->sp.diameter);
			printf("Sphere color r: %d\n", current->sp.color.r);
			printf("Sphere color g: %d\n", current->sp.color.g);
			printf("Sphere color b: %d\n", current->sp.color.b);
		}
		current = current->next;
	}
	
	create_viewport(scene);
	mlx_loop_hook(scene->mlx_ptr, (t_hookfunc)render_image, scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
