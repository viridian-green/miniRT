/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/28 14:38:26 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*normalize_whitespace(char *line)
{
	char	*normalized;
	char	*temp;
	char	*token;
	int		len;

	len = ft_strlen(line);
	normalized = malloc(len + 1);
	if (!normalized)
		return (NULL);
	normalized[0] = '\0';
	temp = ft_strtrim(line, " \t");
	token = ft_strtok(temp, " \t");
	while (token != NULL)
	{
		ft_strcat(normalized, token);
		token = ft_strtok(NULL, " \t");
		if (token)
			ft_strcat(normalized, " ");
	}
	free(temp);
	return (normalized);
}

int	skip_lines(char *line)
{
	if (line[0] == '\0' || line[0] == '\n' || \
		line[0] == '#' || ft_strncmp(line, "//", 2) == 0)
		return (1);
	return (0);
}

void	handle_line(char *line, t_scene *scene, int *counts)
{
	if (ft_strncmp(line, "A", 1) == 0)
		handle_ambience(line, scene, counts);
	else if (ft_strncmp(line, "C", 1) == 0)
		handle_camera(line, scene, counts);
	else if (ft_strncmp(line, "L", 1) == 0)
		handle_light(line, scene, counts);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "sp", 2) == 0)
		parse_sphere(line, scene);
	else if (ft_strncmp(line, "cy", 2) == 0)
		parse_cylinder(line, scene);
	else
		free_exit("Error. Incorrect file.\n", scene, 1);
}

void	parse_file(int fd, t_scene *scene)
{
	char	*line;
	char	*normalized_line;
	int		counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		normalized_line = normalize_whitespace(line);
		if (!skip_lines(normalized_line))
			handle_line(normalized_line, scene, counts);
		free(normalized_line);
		free(line);
		line = get_next_line(fd);
	}
}

int	parsing(char *config_file, t_scene *scene)
{
	int	fd;

	fd = 0;
	fd = open(config_file, O_RDONLY);
	if (fd < 0)
		free_exit("Error. Incorrect file or fd.\n", scene, 1);
	parse_file(fd, scene);
	close(fd);
	return (0);
}
