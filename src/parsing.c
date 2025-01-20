/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 16:42:28 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parse_light(char *line, t_scene *scene)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	scene->light.diameter = ft_atoi(split_line[2]);
	printf("%s", split_line[2]);
	set_color(&split_line[3], &scene->light.color);
	printf("%d", scene->light.color.r);
}

void parse_file(int fd, t_scene *scene)
{
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
	if (ft_strncmp(line, "A", 1) == 0)
		parse_ambience(line, scene);
	 if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(line, scene);
	else if (ft_strncmp(line, "L", 1) == 0)
		parse_light(line, scene);
	 if (ft_strncmp(line, "pl", 1) == 0)
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