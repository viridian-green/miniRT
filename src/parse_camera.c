/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:38:17 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 15:56:24 by ademarti         ###   ########.fr       */
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

int	set_coordinates(char **line, t_scene *scene)
{
	double x;
	double y;
	double z;

	split_double(line[1], &x, &y, &z);
	scene->camera.viewpoint.x = x;
	scene->camera.viewpoint.y = y;
	scene->camera.viewpoint.z = z;
	return (0);
}
int	set_orientation(char **line, t_scene *scene)
{
	double x;
	double y;
	double z;

	split_double(line[1], &x, &y, &z);
	scene->camera.orientation.y = y;
	scene->camera.orientation.y = y;
	scene->camera.orientation.z = z;
	return (0);
}
void parse_camera(char *line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], scene);
	set_orientation(&split_line[1], scene);
	scene->camera.fov = ft_atoi(split_line[2]);
}