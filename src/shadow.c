/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:25:00 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/17 17:30:08 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//origin of shadow origin should be a little bit offset from the intersection point (light)
int	check_shadow(t_scene *scene, t_ray light, t_intersec intersec)
{
	t_ray	shadow;
	double	hit;
	double	len_to_light;

	shadow.direction = light.direction;
	shadow.origin = vc_add(intersec.point, vc_mult_scalar(intersec.normal, EPSILON));
	len_to_light = vc_length(vc_subtract(light.origin, shadow.origin));
	while (scene->object)
	{
		hit = 0;
		hit = object_intersects(*scene->object, shadow, hit, scene);
		if (hit && hit > EPSILON && hit < (len_to_light - EPSILON))
			return (1);
		scene->object = scene->object->next;
	}
	return (0);
}