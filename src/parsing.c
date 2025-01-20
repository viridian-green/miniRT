/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:51:35 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 14:04:38 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


double ft_atod(const char *str) {
    double result = 0.0;
    double decimalPlace = 1.0;
    int sign = 1;
    int decimalFound = 0;

    // Handle negative numbers
    if (*str == '-') {
        sign = -1;
        str++;
    }

    // Process each character
    while (*str != '\0') {
        if (*str == '.') {
            decimalFound = 1;  // Found the decimal point
        } else if (ft_isdigit(*str)) {
            int digit = *str - '0';

            if (decimalFound) {
                decimalPlace *= 0.1;
                result += digit * decimalPlace;
            } else {
                result = result * 10 + digit;
            }
        } else {
            // If non-numeric character, break
            break;
        }
        str++;
    }

    return result * sign;
}

void split_three(char **line, int *one, int *two, int *three)
{
    char **split_line;

    split_line = ft_split(*line, ',');

	 if (!split_line || !split_line[0] || !split_line[1] || !split_line[2])
    {
        exit(EXIT_FAILURE); // Handle error appropriately
    }
    *one = ft_atod(split_line[0]);
    *two = ft_atod(split_line[1]);
    *three = ft_atod(split_line[2]);
}

int	set_coordinates(char *input_coords, double *x, double *y, double *z)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (-1);
	*x = atof(coords[0]);
	*y = atof(coords[1]);
	*z = atof(coords[2]);
	return (0);
}
void parse_camera(char *line, t_scene *scene)
{
	char **split_line;
	split_line = ft_split(line, ' ');
	double x;
	double y;
	double z;
	set_coordinates(split_line[1], &x, &y, &z);
	scene->camera.viewpoint.x = x;
	scene->camera.viewpoint.y = y;
	scene->camera.viewpoint.z = z;
	printf("%f", scene->camera.viewpoint.z);
	// set_viewpoint(&split_line[1], scene);
}

// void set_viewpoint(char **line, t_scene *scene)
// {
// 	printf("hey");
// 	double x;
// 	double y;
// 	double z;

// 	set_coordinates(&line[0], &x, &y, &z);
// 	// split_three_(&split_line[1]);
// 	scene->camera->viewpoint.x = 2.00;
// 	// scene->camera->viewpoint.x = (float)x;
// 	// printf("%d", x);
// 	// printf("%f", scene->camera->viewpoint.x);
// }


// char	**split_three_(char *info)
// {
// 	int		i;
// 	int		comma_count;
// 	char	**str_arr;

// 	i = -1;
// 	comma_count = 0;
// 	while (info[++i])
// 	{
// 		if (info[i] == ',')
// 			comma_count++;
// 	}
// 	if (comma_count != 2)
// 		return (NULL);
// 	str_arr = ft_split(info, ',');
// 	if (ft_arr_len(str_arr) != 3)
// 		return (NULL);
// 	return (str_arr);
// }



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