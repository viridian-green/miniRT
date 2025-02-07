/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:11:01 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/07 15:37:06 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WIDTH 1280
# define HEIGHT 720
# define EPSILON 1e-6

# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_ambience
{
	double		light_ratio;
	t_color		color;
}	t_ambience;

//FOV: Angle of what you see.
typedef struct s_camera
{
	t_vector	origin;
	t_vector	forward_v;
	t_vector	right_v;
	t_vector	up_v;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector	light_point;
	double		ratio;
	t_color		color;
}	t_light;

typedef struct s_sp
{
	t_vector	center;
	double		diameter;
	t_color		color;
}	t_sp;

typedef struct s_pl
{
	t_vector	plane_point;
	t_vector	orientation;
	t_color		color;
}	t_pl;

typedef struct s_cy
{
	t_vector	center;
	t_vector	orientation;
	double		diameter;
	double		height;
	t_color		color;
}	t_cy;

typedef struct s_intersec
{
	double			t;
	t_vector			point;
	t_vector			normal;
	t_color			color;
	char			type;
	struct s_object	*self;
}	t_intersec;

//type 1 = sphere, type 2 = plane, type 3 = cylinder
typedef struct s_object
{
	int				type;
	t_sp			sp;
	t_pl			pl;
	t_cy			cy;
	struct s_object	*next;
}	t_object;

//understand the attributes of the viewport
typedef struct s_viewp
{
	double		width;
	double		height;
	t_vector	center;
	t_vector	up_left;
	t_vector	pixel_init;
	t_vector	pixel_x;
	t_vector	pixel_y;
}	t_viewp;

typedef struct s_scene
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*img;
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
	double		canvas_height;
	double		canvas_width;
	t_viewp		vp;
	t_object	*objects;
}	t_scene;

#endif

