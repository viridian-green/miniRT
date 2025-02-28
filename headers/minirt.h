/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/28 14:43:06 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define M_PI 3.14159265358979323846
# define FOCAL_LENGTH 1.0
# define WIDTH 1200
# define HEIGHT 675
# define EPSILON 1e-6

# define ERR_MEMORY_ALLOC "Error: Memory allocation failed.\n"
# define ERR_INVAL_AMBIENCE "Error: Invalid ambience parameters.\n"
# define ERR_INVAL_A_RATIO "Error: Invalid ambience light ratio.\n"
# define ERR_INVAL_A_FORMAT "Error: Invalid ambience format.\n"
# define ERR_INVAL_C_FORMAT "Error: Invalid camera format.\n"
# define ERR_INVAL_FOV "Error: Invalid camera FOV.\n"
# define ERR_INVAL_COORD_FOV "Error: Invalid camera coordinates or FOV.\n"
# define ERR_INVAL_L_FORMAT "Error: Invalid light format.\n"
# define ERR_INVAL_L_DIAM "Error: Invalid light diameter.\n"
# define ERR_INVAL_LIGHT "Error: Invalid light parameters.\n"
# define ERR_INVAL_S_FORMAT "Error: Invalid sphere format.\n"
# define ERR_INVAL_S_DIAM "Error: Invalid sphere diameter.\n"
# define ERR_INVAL_S_PARAMS "Error: Invalid sphere parameters.\n"
# define ERR_INVAL_PL_FORMAT "Error: Invalid plane format.\n"
# define ERR_INVAL_PL_PARAMS "Error: Invalid plane parameters.\n"
# define ERR_INVAL_CY_FORMAT "Error: Invalid cylinder format.\n"
# define ERR_INVAL_CY_DIMEN "Error: Invalid cylinder dimensions.\n"
# define ERR_INVAL_CY_PARAMS "Error: Invalid cylinder parameters.\n"

# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../libs/get_next_line/get_next_line.h"
# include "../libs/libft/libft.h"
# include "structures.h"

typedef void	(*t_mlx_keyfunc)(mlx_key_data_t kay, void* param);
typedef void	(*t_hookfunc)(void* param);

//checks_2
int			validate_line_format(char **split_line, int expected_params);
int			validate_numeric_value(char *str);
int			ft_strcmp(char*s1, char*s2);
int			validate_name(char*str);

//checks
int			validate_orientation(t_vector *vector);
int			validate_color(t_color *color);
int			validate_diameter(double diameter);
int			validate_height(double height);
int			validate_fov(int fov);

//color_op
t_color		color_add(t_color color1, t_color color2);
t_color		color_mult(t_color color, double ratio);

//color
void		set_color(char **line, t_color *color);
t_color		color_init(double r, double g, double b);
int			convert_color(t_color color);
void		put_color_pixel(double p_x, double p_y, t_scene *scene, t_ray ray);

//cylinder_utils
void		is_cap_or_side_closer(t_results *r, t_object *object, \
									double *t, t_scene *s);
void		find_t1(t_results *r, t_ray ray, t_object object);
void		find_t2(t_results *r, t_ray ray, t_object object, \
					double t_cylinder);
double		find_discriminant(t_results *r, t_ray ray, t_object object);
void		intersections_caps(t_results *r, t_ray ray, t_object object);

//error handling
void		free_linked_list(t_object *object);
int			is_in_linked_list(t_object *head, t_object *target);
int			free_exit(char *message, t_scene *scene, int exit_value);
void		free_split(char **split);
void		handle_parse_error(char **split_l, t_scene *scene, char *message);

//init
void		init_mlx(t_scene *scene);

//intersection
double		object_intersects(t_object object, t_ray ray, double t, t_scene *s);
void		up_closest_intersec(t_scene *s, t_ray ray, t_object *c_o, \
								double c_t);
void		find_nearest_intersection(t_ray ray, t_scene *s);

//lights
t_color		find_diffuse_color(t_scene *scene);
t_color		light_calc(t_scene *scene);

//main
void		key_board(mlx_key_data_t key, t_scene *scene);
void		render_image(t_scene *scene);

//math_2
double		vc_dot(t_vector v1, t_vector v2);
float		vc_length(t_vector v);
t_vector	vectorize_t(t_ray r, double t);
t_vector	vc_normalize(t_vector v);

//math
t_vector	vc_add(t_vector v1, t_vector v2);
t_vector	vc_subtract(t_vector v1, t_vector v2);
t_vector	vc_mult_scalar(t_vector v, double scalar);
t_vector	vc_cross_product(t_vector v1, t_vector v2);

//parse_ambience
int			split_int(char **line, int *one, int *two, int *three);
void		parse_ambience(char *line, t_scene *scene);

//parse_camera
int			split_double(char *input_coords, double *x, double *y, double *z);
int			set_coordinates(char **line, t_vector *point);
int			set_orientation(char **line, t_vector *vector);
void		parse_camera(char *line, t_scene *scene);

//parse_light
int			validate_light_ratio(double ratio);
void		parse_light(char *line, t_scene *scene);

//parse_objects
t_object	*new_object_node(void);
void		add_node_to_object(t_object **head, t_object *node);
void		parse_plane(char *line, t_scene *scene);
void		parse_sphere(char *line, t_scene *scene);
void		parse_cylinder(char *line, t_scene *scene);

//parsing_utils
void		handle_ambience(char *line, t_scene *scene, int *counts);
void		handle_camera(char *line, t_scene *scene, int *counts);
void		handle_light(char *line, t_scene *scene, int *counts);

//parsing
char		*normalize_whitespace(char *line);
int			skip_lines(char *line);
void		handle_line(char *line, t_scene *scene, int *counts);
void		parse_file(int fd, t_scene *scene);
int			parsing(char *config_file, t_scene *scene);

//ray
t_ray		create_ray(double p_x, double p_y, t_vector origin, t_scene *scene);
void		ray_intersects_sp(t_ray ray, t_object object, \
								double *t, t_scene *s);
void		ray_intersects_pl(t_ray ray, t_object object, \
								double *t, t_scene *s);
void		ray_intersects_cy(t_ray ray, t_object object, \
								double *t, t_scene *s);

//shadow
int			check_shadow(t_scene *scene, t_ray light, t_intersec intersec);

//utils
double		ft_atof(const char *str);
char		*ft_strtok(char *str, const char *delim);
char		*ft_strcat(char *dest, const char *src);
double		process_integer_part(const char **str);

//viewport
int			is_aligned_with_up_vector(t_vector orientation);
void		scalarize_pixels(t_scene *s);
void		create_viewport(t_scene *s);

#endif
