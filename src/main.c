/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/10 14:34:49 by ademarti         ###   ########.fr       */
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
	create_viewport(scene);
	// printf("viewport width: %f\n", scene->vp.width);
	// printf("viewport height: %f\n", scene->vp.height);
	// printf("viewport center x: %f\n", scene->vp.center.x);
	// printf("viewport center y: %f\n", scene->vp.center.y);
	// printf("viewport center z: %f\n", scene->vp.center.z);
	// printf("viewport up_left x: %f\n", scene->vp.up_left.x);
	// printf("viewport up_left y: %f\n", scene->vp.up_left.y);
	// printf("viewport up_left z: %f\n", scene->vp.up_left.z);
	// printf("viewport pixel_init x: %f\n", scene->vp.pixel_init.x);
	// printf("viewport pixel_init y: %f\n", scene->vp.pixel_init.y);
	// printf("viewport pixel_init z: %f\n", scene->vp.pixel_init.z);
	// printf("viewport pixel_x x: %f\n", scene->vp.pixel_x.x);
	// printf("viewport pixel_x y: %f\n", scene->vp.pixel_x.y);
	// printf("viewport pixel_x z: %f\n", scene->vp.pixel_x.z);
	// printf("viewport pixel_y x: %f\n", scene->vp.pixel_y.x);
	// printf("viewport pixel_y y: %f\n", scene->vp.pixel_y.y);
	// printf("viewport pixel_y z: %f\n", scene->vp.pixel_y.z);
	mlx_loop_hook(scene->mlx_ptr, (t_hookfunc)render_image, scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
