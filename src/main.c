/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/05 18:00:51 by ademarti         ###   ########.fr       */
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

/*
void	my_mlx_pixel_put(int x, int y, t_fractal *fractal, int color)
{
	int	offset;

	offset = (y * fractal->image.size_line) + ((fractal->image.bpp / 8) * x);
	*(unsigned int *)(fractal->image.pixel + offset) = color;
}
*/

/*
void	render_image(t_scene *scene)
{
	double		pixel_x;
	double		pixel_y;
	t_ray		ray;
	uint8_t red = 255;
	uint8_t green = 0;
	uint8_t blue = 0;

// Combine the components into a single uint32_t
	uint8_t color = (red << 16) | (green << 8) | blue;

	pixel_x = 0;
	while (pixel_x < scene->img->width)
	{
		pixel_y = 0;
		while (pixel_y < scene->img->height)
		{
			ray = create_ray(pixel_x, pixel_y, scene->camera.origin, scene);
			//put_color_to_pixel(pixel_x, pixel_y, scene, ray);
			mlx_put_pixel(scene->img, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}
*/

void render_image(t_scene *scene)
{
    double pixel_x;
    double pixel_y;
    t_ray ray;
    uint32_t color;

    uint8_t red = 255;
    uint8_t green = 0;
    uint8_t blue = 0;

    color = (red << 16) | (green << 8) | blue;

    pixel_x = 0;
    while (pixel_x < scene->img->width)
    {
        pixel_y = 0;
        while (pixel_y < scene->img->height)
        {
            ray = create_ray(pixel_x, pixel_y, scene->camera.origin, scene);
            //put_color_to_pixel(pixel_x, pixel_y, scene, ray);
            mlx_put_pixel(scene->img, pixel_x, pixel_y, 0x000000);
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
	create_viewport(scene);
	//mlx_loop_hook(scene->mlx_ptr, render_image, scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
