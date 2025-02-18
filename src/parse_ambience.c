/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:02:45 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/18 15:20:31 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	split_int(char **line, int *one, int *two, int *three)
{
	char	**split_line;

	split_line = ft_split(*line, ',');
	if (!split_line || !split_line[0] || !split_line[1] || !split_line[2])
	{
		free_split(split_line);
		return (-1);
	}
	*one = ft_atoi(split_line[0]);
	*two = ft_atoi(split_line[1]);
	*three = ft_atoi(split_line[2]);
	free_split(split_line);
	return (0);
}

void	set_color(char **line, t_color *color)
{
	int	r;
	int	g;
	int	b;

	split_int(&line[0], &r, &g, &b);
	color->r = r;
	color->g = g;
	color->b = b;
}

void	parse_ambience(char *line, t_scene *scene)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (validate_line_format(split_line, 3))
		handle_parse_error(split_line, scene, "Error. Invalid ambience format.");
	if (validate_numeric_value(split_line[1]))
		handle_parse_error(split_line, scene, "Error. Invalid ambience light ratio.");
	scene->ambience.light_ratio = ft_atof(split_line[1]);
	set_color(&split_line[2], &scene->ambience.color);
	if (validate_light_ratio(scene->ambience.light_ratio) || \
		validate_color(&scene->ambience.color))
		handle_parse_error(split_line, scene, "Error. Invalid ambience parameters.");
	free_split(split_line);
}
