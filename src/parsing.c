/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 14:56:49 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parse_light(char *line, t_scene *scene)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->light.light_point);
	scene->light.diameter = ft_atof(split_line[2]);
	set_color(&split_line[3], &scene->light.color);
}

void parse_plane(char *line, t_scene *scene)
{
    char **split_line;

	split_line = ft_split(line, ' ');
    set_coordinates(&split_line[0], &scene->pl.plane_point);
    set_orientation(&split_line[1], &scene->pl.normal_vector);
    set_color(&split_line[3], &scene->pl.color);
    //printf("%d", scene->pl.color.b);
}

void parse_sphere(char *line, t_scene *scene)
{
    char **split_line;

	split_line = ft_split(line, ' ');
    set_coordinates(&split_line[0], &scene->sp.center);
    scene->sp.diameter = ft_atof(split_line[2]);
    set_color(&split_line[3], &scene->sp.color);
    //printf("%d", scene->sp.color.r);
}

void parse_cylinder(char *line, t_scene *scene)
{
    char **split_line;

	split_line = ft_split(line, ' ');
    set_coordinates(&split_line[0], &scene->cy.center);
    set_orientation(&split_line[1], &scene->cy.axis);
    scene->cy.diameter = ft_atof(split_line[3]);
    scene->cy.height = ft_atof(split_line[4]);
    set_color(&split_line[5], &scene->sp.color);
    printf("Coordinates: (%f, %f, %f)\n", scene->cy.center.x, scene->cy.center.y, scene->cy.center.z);
    printf("Orientation: (%f, %f, %f)\n", scene->cy.axis.x, scene->cy.axis.y, scene->cy.axis.z);
    printf("Diameter: %f\n", scene->cy.diameter);
    printf("Height: %f\n", scene->cy.height);
    printf("Color: (%d, %d, %d)\n", scene->cy.color.r, scene->cy.color.g, scene->cy.color.b);
}

char *normalize_whitespace(char *line)
{
    char *normalized;
    char *temp;
    char *token;
    int len;

	len = ft_strlen(line);
    normalized = malloc(len + 1);
    if (!normalized)
        return NULL;
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

void parse_file(int fd, t_scene *scene)
{
    char *line;
    char *normalized_line;

    while ((line = get_next_line(fd)) != NULL)
    {
        normalized_line = normalize_whitespace(line);
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
        free(normalized_line);
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