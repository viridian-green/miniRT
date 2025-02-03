/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/04 00:33:43 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	init_mlx(t_scene *scene)
{
	scene->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!scene->mlx_ptr)
		free_exit("Error initializing mlx.", scene);
	scene->img = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
	if (!scene->img)
		free_exit("Error initializing mlx image.", scene);
}

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
//need to understand better
t_ray	create_ray(double pixel_x, double pixel_y, t_vector vp, t_scene *scene)
{
	t_ray		ray;
	t_vector	center;
	t_vector	p_x_sc;
	t_vector	p_y_sc;

	p_x_sc = vector_multiply(scene->vp.pixel_x, pixel_x);
	p_y_sc = vector_multiply(scene->vp.pixel_y, pixel_y);
	center = vector_add(vector_add(scene->vp.pixel_init, p_x_sc), p_y_sc);
	ray.origin = vp;
	ray.direction = vector_subtract(center, vp);
	return (ray);
}
//need to implement
void	put_color_to_pixel(double p_x, double p_y, t_scene *scene, t_ray ray)
{
	(void)p_x;
	(void)p_y;
	(void)scene;
	(void)ray;
}

 //not correct yet
void	render_image(t_scene *scene)
{
	double		pixel_x;
	double		pixel_y;
	t_ray		ray;

	pixel_x = 0;
	while (pixel_x < scene->img->width)
	{
		pixel_y = 0;
		while (pixel_y < scene->img->height)
		{
			ray = create_ray(pixel_x, pixel_y, scene->camera.viewpoint, scene);
			put_color_to_pixel(pixel_x, pixel_y, scene, ray);
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
	//init_scene(scene);
	parsing(av[1], scene);
	create_viewport(scene);
	//mlx_loop_hook(scene->mlx_ptr, render_image, scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
