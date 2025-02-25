/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/25 12:54:57 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define M_PI 3.14159265358979323846
# define FOCAL_LENGTH 1.0
# define WIDTH 1200
# define HEIGHT 675
# define EPSILON 1e-6

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

//checks
int			validate_orientation(t_vector *vector);
int			validate_color(t_color *color);
int			validate_diameter(double diameter);
int			validate_height(double height);
int			validate_fov(int fov);

//color
int			convert_color(t_color color);
void		put_color_pixel(double p_x, double p_y, t_scene *scene, t_ray ray);

//error handling
void		free_linked_list(t_object *object);
int			is_in_linked_list(t_object *head, t_object *target);
int			free_exit(char *message, t_scene *scene, int exit_value);
void		free_split(char **split);
void		handle_parse_error(char **split_l, t_scene *scene, char *message);

//init
void		init_mlx(t_scene *scene);

//lights
t_color		color_add(t_color color1, t_color color2);
t_color		color_mult(t_color color, double ratio);
t_color		color_init(double r, double g, double b);
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
void		set_color(char **line, t_color *color);
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

//parsing
int			validate_line_format(char **split_line, int expected_params);
char		*normalize_whitespace(char *line);
int			skip_lines(char *line);
void		parse_file(int fd, t_scene *scene);
int			parsing(char *config_file, t_scene *scene);

//ray

//shadow
int			check_shadow(t_scene *scene, t_ray light, t_intersec intersec);

//utils
double		process_integer_part(const char **str);
double		ft_atof(const char *str);
char		*ft_strtok(char *str, const char *delim);
char		*ft_strcat(char *dest, const char *src);
int			validate_numeric_value(char *str);

//viewport
int			is_aligned_with_up_vector(t_vector orientation);
void		scalarize_pixels(t_scene *s);
void		create_viewport(t_scene *s);

//Intersections
double	ray_intersects_sp(t_ray ray, t_object object, double *t, t_scene *s);
int ray_intersects_cy(t_ray ray, t_object object, double *t, t_scene *s);
int ray_intersects_pl(t_ray ray, t_object object, double *t, t_scene *s);

t_ray	create_ray(double p_x, double p_y, t_vector origin, t_scene *scene);

double object_intersects(t_object object, t_ray ray, double t, t_scene *s);
void find_nearest_intersection(t_ray ray, t_scene *s);

#endif
