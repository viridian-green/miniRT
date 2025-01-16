/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/16 18:08:01 by mrabelo-         ###   ########.fr       */
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
void	parse_file(int fd, t_scene *scene);
void	parse_camera(char *line, t_scene *scene);
void	parse_ambient(char *line, t_scene *scene);
void	split_three(char **line, int *one, int *two, int *three);

#endif
