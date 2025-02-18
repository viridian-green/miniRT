/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/18 15:30:04 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_format(char **split_line, int expected_params)
{
	int	i;

	i = 0;
	while (split_line[i] != NULL)
		i++;
	if (i != expected_params)
		return (1);
	return (0);
}

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

int skip_lines(char *line)
{
	if (line[0] == '\0' || line[0] == '\n' ||
	line[0] == '#' || ft_strncmp(line, "//", 2) == 0)
		return 1;
	return 0;
}

void	parse_file(int fd, t_scene *scene)
{
	char	*line;
	char	*normalized_line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		normalized_line = normalize_whitespace(line);
		if (skip_lines(normalized_line))
		{
			free(normalized_line);
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (ft_strncmp(normalized_line, "A", 1) == 0)
			parse_ambience(normalized_line, scene);
		else if (ft_strncmp(normalized_line, "C", 1) == 0)
			parse_camera(normalized_line, scene);
		else if (ft_strncmp(normalized_line, "L", 1) == 0)
			parse_light(normalized_line, scene);
		else if (ft_strncmp(normalized_line, "pl", 2) == 0)
			parse_plane(normalized_line, scene);
		else if (ft_strncmp(normalized_line, "sp", 2) == 0)
			parse_sphere(normalized_line, scene);
		else if (ft_strncmp(normalized_line, "cy", 2) == 0)
			parse_cylinder(normalized_line, scene);
		else
			free_exit("Error. Incorrect file.\n", scene);
		free(normalized_line);
		free(line);
		line = get_next_line(fd);
	}
}

int	parsing(char *config_file, t_scene *scene)
{
	int	fd;

	fd = 0;
	if (fd < 0)
		free_exit("Error. Incorrect fd.\n", scene);
	fd = open(config_file, O_RDONLY);
	parse_file(fd, scene);
	close(fd);
	return (0);
}
