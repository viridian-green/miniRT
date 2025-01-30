/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:11:01 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/30 17:48:48 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WIDTH 1280
# define HEIGHT 720

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

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_ambience
{
	double		light_ratio;
	t_color		color;
}	t_ambience;

//FOV: Angle of what you see.
typedef struct s_camera
{
	t_coord		view_point;
	t_vector	orientation;
	int			fov;
}	t_camera;

typedef struct s_viewport
{
    t_point lower_left_corner;
    t_vector horizontal;
    t_vector vertical;
} t_viewport;

typedef struct s_light
{
	t_coord	light_point;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_sp
{
	t_coord	center;
	double	diameter;
	t_color	color;
}	t_sp;

typedef struct s_pl
{
	t_coord		plane_point;
	t_vector	orientation;
	t_color		color;
}	t_pl;

typedef struct s_cy
{
	t_coord		center;
	t_vector	orientation;
	double		diameter;
	double		height;
	t_color		color;
}	t_cy;

typedef struct s_viewp
{
	double width;
	double height;
}	t_viewp;

typedef struct s_scene
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*img;
	t_ambience	ambience;
	t_camera	camera;
	t_viewp vp;
	t_light light;
	t_sp sp;
	t_pl pl;
	t_cy cy;
	double canvas_width;
	double canvas_height;
}	t_scene;

#endif

