/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:04:37 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/23 18:05:22 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->pl.plane_point);
	set_orientation(&split_line[1], &scene->pl.normal_vector);
	set_color(&split_line[3], &scene->pl.color);
	//printf("%d", scene->pl.color.b);
	if (validate_coordinates(&scene->pl.plane_point) || \
		validate_color(&scene->pl.color))
		free_exit("Error. Invalid plane parameters.", scene);
}

void	parse_sphere(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->sp.center);
	scene->sp.diameter = ft_atof(split_line[2]);
	set_color(&split_line[3], &scene->sp.color);
	//printf("Color: (%d, %d, %d)\n", scene->pl.color.r, scene->pl.color.g, scene->pl.color.b);
	if (validate_coordinates(&scene->sp.center) || \
		validate_diameter(scene->sp.diameter) || \
		validate_color(&scene->sp.color))
		free_exit("Error. Invalid sphere parameters.", scene);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->cy.center);
	set_orientation(&split_line[1], &scene->cy.axis);
	scene->cy.diameter = ft_atof(split_line[3]);
	scene->cy.height = ft_atof(split_line[4]);
	set_color(&split_line[5], &scene->cy.color);
	if (validate_coordinates(&scene->cy.center) || \
		validate_diameter(scene->cy.diameter) || \
		validate_height(scene->cy.height) || \
		validate_color(&scene->cy.color))
		free_exit("Error. Invalid cylinder parameters.", scene);
}
