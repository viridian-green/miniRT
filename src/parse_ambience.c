/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:02:45 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 12:36:19 by ademarti         ###   ########.fr       */
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

void set_color(char **line, t_color *color)
{
    int r;
    int g;
    int b;
    split_int(&line[0], &r, &g, &b);
    color->r = r;
    color->g = g;
    color->b = b;
}

void parse_ambience(char *line, t_scene *scene)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	scene->ambience.light_ratio = ft_atof(split_line[1]);
	set_color(&split_line[2], &scene->ambience.color);
}