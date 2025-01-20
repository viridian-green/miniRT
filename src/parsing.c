/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 15:09:33 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	split_double(char *input_coords, double *x, double *y, double *z)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (-1);
	*x = ft_atof(coords[0]);
	*y = ft_atof(coords[1]);
	*z = ft_atof(coords[2]);
	return (0);
}

int	set_coordinates(char *line, t_vector *vector)
{
	double x;
	double y;
	double z;

	split_double(line, &x, &y, &z);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (0);
}
void parse_camera(char *line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ' ');
	set_coordinates(split_line[1], scene->camera.viewpoint);
	printf("%f", scene->camera.viewpoint.x);
	set_coordinates(split_line[2], scene->camera.orientation);
	printf("%f", scene->camera.orientation.x);
}

// scene->camera.fov = ft_atoi(split_line[3]);

void parse_file(int fd, t_scene *scene)
{
	char *line;
	(void)scene;
	while ((line = get_next_line(fd)) != NULL)
	{
	if (ft_strncmp(line, "A", 1) == 0)
		parse_ambient(line, scene);
	 if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(line, scene);
	// else if (ft_strncmp(line, "L", 1) == 0)
	// 	parse_light(line, scene);
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