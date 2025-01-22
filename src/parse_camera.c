/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:38:17 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 14:10:36 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	split_double(char *input_coords, double *x, double *y, double *z)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (-1);
	*x = ft_atof(coords[0]);
	*y = ft_atof(coords[1]);
	*z = ft_atof(coords[2]);
	return (0);
}

int	set_coordinates(char **line, t_point *point)
{
	double x;
	double y;
	double z;

	split_double(line[1], &x, &y, &z);
	point->x = x;
	point->y = y;
	point->z = z;
	return (0);
}

int	set_orientation(char **line, t_vector *vector)
{
	double x;
	double y;
	double z;

	split_double(line[1], &x, &y, &z);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (0);
}

void parse_camera(char *line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->camera.viewpoint);
	set_orientation(&split_line[1], &scene->camera.orientation);
	scene->camera.fov = ft_atoi(split_line[3]);
	//printf("%f     ", scene->camera.viewpoint.x);
}