/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/22 15:34:00 by ademarti         ###   ########.fr       */
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

typedef void	(*t_keyfunc)(mlx_key_data_t kay, void* param);

void	init_mlx(t_scene *scene);
void 	cleanup(void);
void	key_board(mlx_key_data_t key, t_scene *scene);

//Init
void init_scene(t_scene *scene);

//Parsing
int		parsing(char *config_file, t_scene *scene);
void parse_ambience(char *line, t_scene *scene);
void parse_camera(char *line, t_scene *scene);
void set_color(char **line, t_color *color);
int	set_coordinates(char **line, t_point *point);
int	set_orientation(char **line, t_vector *vector);

//Utils
double ft_atof(const char *str);
char *ft_strcat(char *dest, const char *src);
char *ft_strtok(char *str, const char *delim);

#endif
