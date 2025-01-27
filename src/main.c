/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/27 14:15:28 by mrabelo-         ###   ########.fr       */
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

void render_image(t_scene *scene)
{
{
	unsigned int		color;
	unsigned int	pixel_x;
	unsigned int	pixel_y;

	pixel_x = 0;
	while (pixel_x < scene->img->width)
	{
		pixel_y = 0;
		while (pixel_y < scene->img->height)
		{
			color = 255;
			mlx_put_pixel(scene->img, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
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
	init_scene(scene);
	parsing(av[1], scene);
	render_image(scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
