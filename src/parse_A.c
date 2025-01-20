/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_A.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:02:45 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/16 16:29:19 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_freearray(char **arr)
{
	int	crstr;
	int	max;

	crstr = 0;
	max = 0;
	while (arr[crstr])
	{
		crstr++;
		max++;
	}
	crstr = 0;
	while (crstr < max)
	{
		free(arr[crstr]);
		arr[crstr] = NULL;
		crstr++;
	}
	free(arr);
	arr = NULL;
	return (0);
}

void set_color(char **line, t_scene *scene)
{
	int r;
	int g;
	int b;
	// r = 0;
	// g = 0;
	// b = 0;
	split_three(&line[0], &r, &g, &b);
	scene->ambient->color.r = r;
	scene->ambient->color.g = g;
	scene->ambient->color.b = b;
}

void parse_ambient(char *line, t_scene *scene)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	scene->ambient->light_ratio = ft_atoi(split_line[1]);
	set_color(&split_line[2], scene);
	// ft_freearray(&line);
}