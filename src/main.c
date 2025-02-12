/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/12 15:26:40 by ademarti         ###   ########.fr       */
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
void render_hit(t_ray ray, double t, t_object *object) {
    t_vector hit_point = vc_add(ray.origin, vc_multiply(ray.direction, t));

    // For now, just set the color based on the object's type
    if (object->type == SPHERE) {
        t_sp *sphere = (t_sp *)object->obj_data;
        set_pixel_color(hit_point, sphere->color);
    } else if (object->type == PLANE) {
        t_pl *plane = (t_pl *)object->obj_data;
        set_pixel_color(hit_point, plane->color);
    }
}
*/

void	render_image(t_scene *scene)
{
    double		pixel_x;
    double		pixel_y;
    t_ray		ray;

    // Set pixel_x and pixel_y to target the center of the canvas
    pixel_x = scene->canvas_width / 2;
    pixel_y = scene->canvas_height / 2;

    // Create a ray for the center pixel
    ray = create_ray(pixel_x, pixel_y, scene->camera.origin, scene);

    // Put the color of the pixel at the center
    put_color_pixel(pixel_x, pixel_y, scene, ray);
}

// void	render_image(t_scene *scene)
// {
// 	double		pixel_x;
// 	double		pixel_y;
// 	t_ray		ray;

// 	pixel_x = 0;
// 	while (pixel_x < scene->canvas_width)
// 	{
// 		pixel_y = 0;
// 		while (pixel_y < scene->canvas_height)
// 		{
// 			ray = create_ray(pixel_x, pixel_y, scene->camera.origin, scene);
// 			put_color_pixel(pixel_x, pixel_y, scene, ray);
// 			pixel_y++;
// 		}
// 		pixel_x++;
// 	}
// }

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
	mlx_loop_hook(scene->mlx_ptr, (t_hookfunc)render_image, scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
