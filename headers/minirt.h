/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/21 12:12:51 by ademarti         ###   ########.fr       */
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
# include "structures.h"
# include "../libs/get_next_line/get_next_line.h"
# include "../libs/libft/libft.h"
// #include "minilibx-linus/mlx.h"

//Parsing
int		parsing(char *config_file, t_scene *scene);
void parse_ambience(char *line, t_scene *scene);
void parse_camera(char *line, t_scene *scene);
void set_color(char **line, t_color *color);
int	set_coordinates(char **line, t_point *point);

//Utils
double ft_atof(const char *str);

#endif
