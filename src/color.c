/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:35:20 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/11 11:15:19 by ademarti         ###   ########.fr       */
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

int object_intersects(t_object object, t_ray ray, double *t)
{
	if (ray_intersects_sp(ray, object, t))
		return (1);
	if (ray_intersects_plane(ray, object, t))
		return (1);
	else if (ray_intersects_cylinder(ray, object, t))
		return (1);
	return (0);
}

void find_nearest_intersection(t_ray ray, t_scene *s)
{
    double closest_t = INT_MAX;
    t_object *current = s->object;  // Temporary pointer to iterate

    s->intersec.self = NULL;  // Reset intersection before finding
    while (current)
    {
        double t;
        if (object_intersects(*current, ray, &t))
        {
            if (t < closest_t)
            {
                closest_t = t;
                s->intersec.self = current;
            }
        }
        current = current->next;  // Move to the next object
    }
}

void	put_color_pixel(double p_x, double p_y, t_scene *scene, t_ray ray)
{
	int			color;
	t_color		rgb;

	(void)ray;
	find_nearest_intersection(ray, scene);
        if (scene->intersec.self->type == 1) // Sphere
            rgb = scene->intersec.self->sp.color;
        else if (scene->intersec.self->type == 2) // Plane
			rgb = scene->intersec.self->pl.color;
        else if (scene->intersec.self->type == 3) // Cylinder
			rgb = scene->intersec.self->cy.color;
        else
            rgb = (t_color){0, 0, 0};
	// rgb = scene->intersec.self->color;
	color = convert_color(rgb);
	mlx_put_pixel(scene->img, p_x, p_y, color);
}
