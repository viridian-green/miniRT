/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:19:18 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/25 15:21:15 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
The function object_intersects is called inside the loop in
find_nearest_intersection to check whether the current object
is intersected by the ray. It modifies t if the intersection is
closer than the previous one.
*/
double	object_intersects(t_object object, t_ray ray, double t, t_scene *s)
{
	ray_intersects_sp(ray, object, &t, s);
	ray_intersects_pl(ray, object, &t, s);
	ray_intersects_cy(ray, object, &t, s);
	return (t);
}

void	up_closest_intersec(t_scene *s, t_ray ray, t_object *c_o, double c_t)
{
	s->intersec.t = c_t;
	s->intersec.self = c_o;
	ray_intersects_sp(ray, *c_o, &c_t, s);
	ray_intersects_pl(ray, *c_o, &c_t, s);
	ray_intersects_cy(ray, *c_o, &c_t, s);
}

void	find_nearest_intersection(t_ray ray, t_scene *s)
{
	double		closest_t;
	double		t;
	t_object	*current;
	t_object	*closest_object;

	closest_t = INFINITY;
	t = -1;
	current = s->object;
	closest_object = NULL;
	s->intersec.self = NULL;
	while (current)
	{
		t = object_intersects(*current, ray, t, s);
		if (t > 0.001 && t < closest_t)
		{
			closest_t = t;
			closest_object = current;
		}
		current = current->next;
	}
	if (closest_object)
		up_closest_intersec(s, ray, closest_object, closest_t);
}
