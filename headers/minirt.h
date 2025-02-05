/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/05 14:17:43 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define M_PI 3.14159265358979323846
# define FOCAL_LENGTH 1.0

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

//checks
int		validate_orientation(t_vector *vector);
int		validate_color(t_color *color);
int		validate_diameter(double diameter);
int		validate_height(double height);
int		validate_fov(int fov);

//error handling
int		free_exit(char *message, t_scene *scene);
void	free_split(char **split);
void	handle_parse_error(char **split_line, t_scene *scene, char *message);

//init
void	init_ambience(t_ambience *ambience);
void	init_camera(t_camera *camera);
void	init_light(t_light *light);
void	init_scene(t_scene *scene);

//init_objects
void	init_sphere(t_sp *sp);
void	init_plane(t_pl *pl);
void	init_cylinder(t_cy *cy);
void	init_object(t_object *obj);

//main
void	init_mlx(t_scene *scene);
void	key_board(mlx_key_data_t key, t_scene *scene);
void	render_image(t_scene *scene);
t_ray	create_ray(double pixel_x, double pixel_y, t_vector vp, t_scene *scene);

//parse_ambience
void	split_int(char **line, int *one, int *two, int *three);
void	set_color(char **line, t_color *color);
void	parse_ambience(char *line, t_scene *scene);

//parse_camera
int		split_double(char *input_coords, double *x, double *y, double *z);
int		set_coordinates(char **line, t_vector *point);
int		set_orientation(char **line, t_vector *vector);
void	parse_camera(char *line, t_scene *scene);

//parse_light
int		validate_light_ratio(double ratio);
void	parse_light(char *line, t_scene *scene);

//parse_objects
void	parse_plane(char *line, t_scene *scene);
void	parse_sphere(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);

//parsing
char	*normalize_whitespace(char *line);
void	parse_file(int fd, t_scene *scene);
int		parsing(char *config_file, t_scene *scene);
int		validate_line_format(char **split_line, int expected_params);

//utils
double	ft_atof(const char *str);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strtok(char *str, const char *delim);
int		validate_numeric_value(char *str);
double	process_integer_part(const char **str);

//math
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_subtract(t_vector v1, t_vector v2);
t_vector	vector_multiply(t_vector v, double scalar);
t_vector	cross_product(t_vector v1, t_vector v2);
float		vector_length(t_vector v);

void	create_viewport(t_scene *s);
#endif
