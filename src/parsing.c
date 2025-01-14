/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/14 16:05:00 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void split_three(char **line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ',');
	scene.ambient.color->r = split_line[0];

}

void parse_ambient(char *line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ' ');
	scene->ambient->light_ratio = ft_atoi(split_line[1]);
	split_three(split_line[2], &scene);
}

void parse_camera(char *line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ' ');
	// scene->camera->viewpoint = ft_atoi(ft_split(split_line[1], ','));
	//scene->ambient->color = split_line[1];
}

void parse_file(int fd, t_scene *scene)
{
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
	if (ft_strncmp(line, "A", 1) == 0)
		parse_ambient(line, scene);
	// else if (ft_strncmp(line, "C", 1) == 0)
	// 	parse_camera(line, scene);
	// else if (ft_strncmp(line, "L", 1) == 0)
	// 	parse_light(line, scene);
	else if (ft_strncmp(line, "pl", 1) == 0)
		printf("you");
	else if (ft_strncmp(line, "sp", 1) == 0)
		printf("today");
	else if (ft_strncmp(line, "cy", 1) == 0)
		printf("?");
	free(line);
	}
}

int parsing(char *config_file, t_scene *scene)
{
	int	fd = 0;

	if (fd < 0)
	{
		perror("Error. Cannot open file.");
		return (1);
	}
	fd = open(config_file, O_RDONLY);
	parse_file(fd, scene);
	close(fd);
	return (0);
}