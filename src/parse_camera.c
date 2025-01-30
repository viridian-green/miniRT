/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:38:17 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/30 19:22:37 by ademarti         ###   ########.fr       */
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

int	set_coordinates(char **line, t_coord *point)
{
	double	x;
	double	y;
	double	z;

	split_double(line[1], &x, &y, &z);
	point->x = x;
	point->y = y;
	point->z = z;
	return (0);
}

int	set_orientation(char **line, t_vector *vector)
{
	double	x;
	double	y;
	double	z;

	split_double(line[1], &x, &y, &z);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (0);
}

void	parse_camera(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->camera.viewpoint);
	set_orientation(&split_line[1], &scene->camera.forward_v);
	scene->camera.fov = ft_atoi(split_line[3]);
	//printf("Parsed FOV: %d\n", scene->camera.fov);
	if (validate_orientation(&scene->camera.forward_v) || \
		validate_fov(scene->camera.fov))
		free_exit("Error: Invalid camera coordinates or FOV", scene);
}
