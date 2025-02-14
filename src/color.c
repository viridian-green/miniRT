/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:35:20 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/13 18:35:36 by mrabelo-         ###   ########.fr       */
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


// int hit_sp(t_ray ray, t_object object, double *t)
// {
// 	t_vector	oc;
//        double	a;
//        double	half_b;
//        double	c;
//        double	discriminant;

//        //s->intersec.self = NULL;

//        oc = vc_subtract(ray.origin, object.sp.center);
//        a = vec_dot(ray.direction, ray.direction);
//        half_b = vec_dot(oc, ray.direction);
//        c = vec_dot(oc, oc) - object.sp.diameter * object.sp.diameter / 4;
//        discriminant = half_b * half_b - a * c;
//        if (discriminant < 0)
//        {
//            return (0);
//        }
//        else
//        {
//         	// s->intersec.self = object;
//         	*t = ((-half_b - sqrt(discriminant)) / a);
// 			return (1);
//        }
// 	   return (0);
// }


double object_intersects(t_object object, t_ray ray, double t, t_scene *s)
{
	(void)s;
	// printf("%fsp\n", t);
	if (ray_intersects_sp(ray, object, &t, s))
	{
		// printf("%fsp\n", t);
	}
	// if (ray_intersects_plane(ray, object, &t))
	// {
	// 	// printf("%fp\n", t);
	// }
	// if (ray_intersects_cylinder(ray, object, &t))
	// {
	// 	printf("%fc\n", t);
	// }
	return (t);
}

void find_nearest_intersection(t_ray ray, t_scene *s)
{
	double closest_t = INFINITY;
	s->intersec.self = NULL;
	double t = -1;
	t_object *current = s->object;  // Start from the head of the linked list
	while (current)
	{
	t = object_intersects(*current, ray, t, s);
	s->intersec.t = t; // Check intersection with the current object
	if (t > 0.001 && t < closest_t)
	{
		// printf("New closest object at t = %f\n", t);
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
		//printf("%d", scene->intersec.self->type);
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
