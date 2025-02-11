/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:35:20 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/11 13:31:03 by ademarti         ###   ########.fr       */
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
	//double t;
	if (hit_sp(ray, object, &t))
	{
		t = ray_intersects_sp(&object, &ray, s);
	}
	if (ray_intersects_plane(ray, object, &t))
	{
		t = ray_intersects_sp(&object, &ray, s);
	}
	if (ray_intersects_cylinder(ray, object, &t))
	{
		printf("ok");
		t = ray_intersects_sp(&object, &ray, s);
	}
	return (t);
}

void find_nearest_intersection(t_ray ray, t_scene *s)
{
    //double closest_t = INT_MAX;
    t_object *current = s->object;  // Temporary pointer to iterate
	double t = -1;
	double temp_t;
    s->intersec.self = NULL;  // Reset intersection before finding
    while (current)
    {
        temp_t = object_intersects(*current, ray, temp_t, s);
        {
            if ((t < 0 && temp_t > 0) || ((temp_t > 0 && temp_t < t)))
            {
                t = temp_t;
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
	if (scene->intersec.self != NULL)
    {
		printf("%d", scene->intersec.self->type);
        if (scene->intersec.self->type == 1) // Sphere
		{
			printf("yes");
            rgb = scene->object->sp.color;
		}
        else if (scene->intersec.self->type == 2) // Plane
        {
			printf("no");
            rgb = scene->object->pl.color;
		}
        else if (scene->intersec.self->type == 3) // Cylinder
		{
			printf("why not");
            //rgb = scene->intersec.self->cy.color;
			rgb = scene->object->cy.color;
		}
        else
            rgb = scene->ambience.color;  // Default to black if type is unknown
    }
    else
    {
		rgb = scene->ambience.color;  //// No intersection, set to background color
    }
	// rgb = scene->intersec.self->color;
	color = convert_color(rgb);
	mlx_put_pixel(scene->img, p_x, p_y, color);
}
