/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:04:37 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/27 18:32:12 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (validate_line_format(split_line, 4))
		free_exit("Error. Invalid plane format.", scene);
	set_coordinates(&split_line[0], &scene->pl.plane_point);
	set_orientation(&split_line[1], &scene->pl.orientation);
	set_color(&split_line[3], &scene->pl.color);
	//printf("%d", scene->pl.color.b);
	if (validate_orientation(&scene->pl.orientation) || \
		validate_color(&scene->pl.color))
		free_exit("Error. Invalid plane parameters.", scene);
}

void	parse_sphere(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (validate_line_format(split_line, 4))
		free_exit("Error. Invalid sphere format.", scene);
	set_coordinates(&split_line[0], &scene->sp.center);
	if (validate_numeric_value(split_line[2]))
		free_exit("Error. Invalid sphere diameter.", scene);
	scene->sp.diameter = ft_atof(split_line[2]);
	set_color(&split_line[3], &scene->sp.color);
	//printf("Color: (%d, %d, %d)\n", scene->pl.color.r, scene->pl.color.g, scene->pl.color.b);
	if (validate_diameter(scene->sp.diameter) || \
		validate_color(&scene->sp.color))
		free_exit("Error. Invalid sphere parameters.", scene);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (validate_line_format(split_line, 6))
		free_exit("Error. Invalid cylinder format.", scene);
	set_coordinates(&split_line[0], &scene->cy.center);
	set_orientation(&split_line[1], &scene->cy.orientation);
	if (validate_numeric_value(split_line[3]) || \
		validate_numeric_value(split_line[4]))
		free_exit("Error. Invalid cylinder dimensions.", scene);
	scene->cy.diameter = ft_atof(split_line[3]);
	scene->cy.height = ft_atof(split_line[4]);
	set_color(&split_line[5], &scene->cy.color);
	if (validate_orientation(&scene->cy.orientation) || \
		validate_diameter(scene->cy.diameter) || \
		validate_height(scene->cy.height) || \
		validate_color(&scene->cy.color))
		free_exit("Error. Invalid cylinder parameters.", scene);
}
