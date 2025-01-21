/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 13:14:26 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parse_light(char *line, t_scene *scene)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	set_coordinates(&split_line[0], &scene->light.light_point);
	scene->light.diameter = ft_atof(split_line[2]);
	//printf("%f", scene->light.light_point.x);
	//printf("%f", scene->light.light_point.y);
	//printf("%f", scene->light.light_point.z);
	//printf("%s", split_line[2]);
	printf("%f", scene->light.diameter);
	set_color(&split_line[3], &scene->light.color);
	//printf("%d", scene->light.color.r);
}

char *normalize_whitespace(char *line)
{
    char *normalized;
    char *temp;
    char *token;
    int len = strlen(line);

    normalized = malloc(len + 1);
    if (!normalized)
        return NULL;
    normalized[0] = '\0';

    temp = ft_strtrim(line, " \t");
    token = strtok(temp, " \t");
    while (token != NULL)
    {
        strcat(normalized, token);
        token = strtok(NULL, " \t");
        if (token)
            strcat(normalized, " ");
    }
    free(temp);
    return normalized;
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
            printf("you");
        else if (ft_strncmp(normalized_line, "sp", 2) == 0)
            printf("today");
        else if (ft_strncmp(normalized_line, "cy", 2) == 0)
            printf("?");
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