/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:54:31 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/27 18:19:47 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_orientation(t_vector *vector)
{
	double	magnitude;

	magnitude = sqrt(vector->x * vector->x + vector->y * \
						vector->y + vector->z * vector->z);
	if (fabs(magnitude - 1.0) > 1e-6)
		return (1);
	return (0);
}

int	validate_color(t_color *color)
{
	if (color->r < 0 || color->r > 255 || color->g < 0 \
		|| color->g > 255 || color->b < 0 || color->b > 255)
		return (1);
	return (0);
}

int	validate_diameter(double diameter)
{
	if (diameter <= 0)
		return (1);
	return (0);
}

int	validate_height(double height)
{
	if (height <= 0)
		return (1);
	return (0);
}

int	validate_fov(int fov)
{
	if (fov < 0 || fov > 180)
		return (1);
	return (0);
}
