/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:11:01 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/16 18:08:10 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_ambient
{
	int		light_ratio;
	t_color	color;
}	t_ambient;

//FOV: Angle of what you see.
typedef struct s_camera
{
	t_point		viewpoint;
	t_vector	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_point	light_point;
	int		diameter;
	t_color	color;
}	t_light;

typedef struct s_sp
{
	t_point	center;
	float	diameter;
	t_color	color;
}	t_sp;

typedef struct s_pl
{
	t_point		plane_point;
	t_vector	normal_vector;
	t_color		color;
}	t_pl;

typedef struct s_cy
{
	t_point		center;
	t_vector	axis;
	float		diameter;
	float		height;
	t_color		color;
}	t_cy;

typedef struct s_scene
{
	void		*mlx_ptr;
	void		*win;
	t_ambient	*ambient;
	t_camera	*camera;
}	t_scene;

#endif
