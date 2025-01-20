/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:02:45 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 14:54:43 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void split_int(char **line, int *one, int *two, int *three)
{
    char **split_line;

    split_line = ft_split(*line, ',');
	 if (!split_line || !split_line[0] || !split_line[1] || !split_line[2])
        exit(EXIT_FAILURE);
    *one = ft_atoi(split_line[0]);
    *two = ft_atoi(split_line[1]);
    *three = ft_atoi(split_line[2]);
}

void set_color(char **line, t_scene *scene)
{
	int r;
	int g;
	int b;
	split_int(&line[0], &r, &g, &b);
	scene->ambient.color.r = r;
	scene->ambient.color.g = g;
	scene->ambient.color.b = b;
}

void parse_ambient(char *line, t_scene *scene)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	scene->ambient.light_ratio = ft_atoi(split_line[1]);
	set_color(&split_line[2], scene);
}