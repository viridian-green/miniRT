/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/21 16:04:48 by mrabelo-         ###   ########.fr       */
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

//Parsing
int		parsing(char *config_file, t_scene *scene);
void parse_ambient(char *line, t_scene *scene);
void parse_camera(char *line, t_scene *scene);

//Utils
double ft_atof(const char *str);

#endif
