/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/27 14:25:30 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../libs/get_next_line/get_next_line.h"
# include "../libs/libft/libft.h"
# include "structures.h"

typedef void	(*t_mlx_keyfunc)(mlx_key_data_t kay, void* param);

void	init_mlx(t_scene *scene);
void	key_board(mlx_key_data_t key, t_scene *scene);

int		validate_orientation(t_vector *vector);
int		validate_light_ratio(double ratio);
int		validate_color(t_color *color);
int		validate_diameter(double diameter);
int		validate_height(double height);
int		validate_fov(int fov);

//Error handlign & mmemory
int		free_exit(char *message, t_scene *scene);

//Init
void	init_scene(t_scene *scene);

//Parsing
char	*normalize_whitespace(char *line);
void	parse_file(int fd, t_scene *scene);
int		parsing(char *config_file, t_scene *scene);
void	set_color(char **line, t_color *color);
int		set_coordinates(char **line, t_coord *point);
int		set_orientation(char **line, t_vector *vector);

void	parse_ambience(char *line, t_scene *scene);
void	parse_camera(char *line, t_scene *scene);
void	parse_light(char *line, t_scene *scene);
void	parse_plane(char *line, t_scene *scene);
void	parse_sphere(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);

//Utils
double	ft_atof(const char *str);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strtok(char *str, const char *delim);

#endif
