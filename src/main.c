/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/13 18:42:20 by mrabelo-         ###   ########.fr       */
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
	printf("=== CAMERA ORIENTATION BEFORE VIEWPORT SETUP ===\n");
	printf("Camera orientation X: %f\n", scene->camera.forward_v.x);
	printf("Camera orientation Y: %f\n", scene->camera.forward_v.y);
	printf("Camera orientation Z: %f\n", scene->camera.forward_v.z);
	printf("======================\n");
	create_viewport(scene);
	printf("=== VIEWPORT INFO ===\n\n");
	printf("=== CAMERA ORIENTATION AFTER VIEWPORT SETUP ===\n");
	printf("Camera orientation X: %f\n", scene->camera.forward_v.x);
	printf("Camera orientation Y: %f\n", scene->camera.forward_v.y);
	printf("Camera orientation Z: %f\n", scene->camera.forward_v.z);
	printf("=== CAMERA RIGHT ===\n");
	printf("Camera right X:  %f\n", scene->camera.right_v.x);
	printf("Camera right Y:  %f\n", scene->camera.right_v.y);
	printf("Camera right Z:  %f\n", scene->camera.right_v.z);
	printf("=== CAMERA UP ===\n");
	printf("Camera up X:  %f\n", scene->camera.up_v.x);
	printf("Camera up Y:  %f\n", scene->camera.up_v.y);
	printf("Camera up Z:  %f\n", scene->camera.up_v.z);
	printf("Camera FOV:  %d\n", scene->camera.fov);
	printf("=== VIEWPORT ===\n");
	printf("Viewport width: %f\n", scene->vp.width);
	printf("Viewport height: %f\n", scene->vp.height);
	printf("Viewport CENTER X:  %f\n", scene->vp.center.x);
	printf("Viewport CENTER Y:  %f\n", scene->vp.center.y);
	printf("Viewport CENTER Z:  %f\n", scene->vp.center.z);
	printf("Viewport UP_LEFT X:  %f\n", scene->vp.up_left.x);
	printf("Viewport UP_LEFT Y:  %f\n", scene->vp.up_left.y);
	printf("Viewport UP_LEFT Z:  %f\n", scene->vp.up_left.z);
	printf("Viewport PIXEL_X X:  %f\n", scene->vp.pixel_x.x);
	printf("Viewport PIXEL_X Y:  %f\n", scene->vp.pixel_x.y);
	printf("Viewport PIXEL_X Z:  %f\n", scene->vp.pixel_x.z);
	printf("Viewport PIXEL_Y X:  %f\n", scene->vp.pixel_y.x);
	printf("Viewport PIXEL_Y Y:  %f\n", scene->vp.pixel_y.y);
	printf("Viewport PIXEL_Y Z:  %f\n", scene->vp.pixel_y.z);
	printf("Viewport PIXEL INIT X:  %f\n", scene->vp.pixel_init.x);
	printf("Viewport PIXEL INIT Y:  %f\n", scene->vp.pixel_init.y);
	printf("Viewport PIXEL INIT Z:  %f\n", scene->vp.pixel_init.z);
	printf("======================\n");
	mlx_loop_hook(scene->mlx_ptr, (t_hookfunc)render_image, scene);
	mlx_key_hook(scene->mlx_ptr, (t_mlx_keyfunc)key_board, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
