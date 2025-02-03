/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:30:18 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/03 16:31:38 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_sphere(t_sp *sp)
{
	sp->center.x = 0;
	sp->center.y = 0;
	sp->center.z = 0;
	sp->diameter = 0;
	sp->color.r = 0;
	sp->color.g = 0;
	sp->color.b = 0;
}

void	init_plane(t_pl *pl)
{
	pl->plane_point.x = 0;
	pl->plane_point.y = 0;
	pl->plane_point.z = 0;
	pl->orientation.x = 0;
	pl->orientation.y = 0;
	pl->orientation.z = 0;
	pl->color.r = 0;
	pl->color.g = 0;
	pl->color.b = 0;
}

void	init_cylinder(t_cy *cy)
{
	cy->center.x = 0;
	cy->center.y = 0;
	cy->center.z = 0;
	cy->orientation.x = 0;
	cy->orientation.y = 0;
	cy->orientation.z = 0;
	cy->diameter = 0;
	cy->height = 0;
	cy->color.r = 0;
	cy->color.g = 0;
	cy->color.b = 0;
}

void	init_object(t_object *obj)
{
	if (obj->type == 1)
		init_sphere(&obj->sp);
	else if (obj->type == 2)
		init_plane(&obj->pl);
	else if (obj->type == 3)
		init_cylinder(&obj->cy);
}
