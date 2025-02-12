/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:35:20 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/12 12:55:20 by ademarti         ###   ########.fr       */
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
	if (ray_intersects_sp(ray, object, &t, s))
	{
		printf("%fsp\n", t);
	}
	if (ray_intersects_plane(ray, object, &t))
	{
		printf("%fp\n", t);
	}
	if (ray_intersects_cylinder(ray, object, &t))
	{
		printf("%fc\n", t);
	}
	return (t);
}

void find_nearest_intersection(t_ray ray, t_scene *s)
{
    //double closest_t = INT_MAX;
    t_object *current = s->object;  // Temporary pointer to iterate
	double t = -1;
	double temp_t = -1;
	s->intersec.self = NULL;
    while (current)
    {
        temp_t = object_intersects(*current, ray, temp_t, s);
        {
            if ((t < 0 && temp_t > 0) || ((temp_t > 0 && temp_t < t)))
            {
                t = temp_t;
				// printf("%f \n", t);
				s->intersec.self = current;
				printf("%d", s->intersec.self->type);
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
			printf("sphere");
            rgb = scene->object->sp.color;
		}
        if (scene->intersec.self->type == 2) // Plane
        {
			printf("plane");
            rgb = scene->object->pl.color;
		}
        if (scene->intersec.self->type == 3) // Cylinder
		{
			printf("cylinder");
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
