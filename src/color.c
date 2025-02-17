/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:35:20 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/17 17:24:02 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

int	convert_color(t_color color)
{
	int	rgb;
	int	opacity;

	opacity = 255;
	rgb = (color.r << 24) + (color.g << 16) + (color.b << 8) + opacity;
	return (rgb);
}

double object_intersects(t_object object, t_ray ray, double t, t_scene *s)
{
	if (s->object->type == 1)
    	ray_intersects_sp(ray, object, &t, s);
    if (s->object->type == 2)
		ray_intersects_plane(ray, object, &t);
    if (s->object->type == 3)
		ray_intersects_cylinder(ray, object, &t);
	// printf("my_t %f\n", s->intersec.t);
	// printf("t: %f\n", t);
	return (t);
}

void find_nearest_intersection(t_ray ray, t_scene *s)
{
	double closest_t = INFINITY;
	s->intersec.self = NULL;
	double t = -1;
	t_object *current = s->object;
	while (current)
	{
	t = object_intersects(*current, ray, t, s);
	// t = s->intersec.t;
	if (t > 0.001 && t < closest_t)
	{
		closest_t = t;
		s->intersec.self = current;
	}
	current = current->next;
}
}

void	put_color_pixel(double p_x, double p_y, t_scene *scene, t_ray ray)
{
	int			color;
	t_color		rgb;

	(void)ray;
	find_nearest_intersection(ray, scene);
	if (scene->intersec.self != NULL)
    {
        if (scene->intersec.self->type == 1) // Sphere
		{
			//printf("sphere");
            rgb = scene->object->sp.color;
		}
        if (scene->intersec.self->type == 2) // Plane
        {
			//printf("plane");
            rgb = scene->object->pl.color;
		}
        if (scene->intersec.self->type == 3) // Cylinder
		{
			//printf("cylinder");
			rgb = scene->object->cy.color;
		}
    }
    else
    {
		rgb = scene->ambience.color;
    }
	color = convert_color(rgb);
	mlx_put_pixel(scene->img, p_x, p_y, color);
}
