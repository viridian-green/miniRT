/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/22 15:53:18 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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
