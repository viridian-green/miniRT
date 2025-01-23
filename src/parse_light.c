/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:04:39 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/23 18:05:01 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_light(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->light.light_point);
	scene->light.diameter = ft_atof(split_line[2]);
	set_color(&split_line[3], &scene->light.color);
	if (validate_coordinates(&scene->light.light_point) || \
		validate_diameter(scene->light.diameter) || \
		validate_color(&scene->light.color))
		free_exit("Error. Invalid light parameters.", scene);
}
