/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:23 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/27 15:41:16 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Check if the camera orientation is aligned with world-up or its negative
*/
int	is_aligned_with_up_vector(t_vector orientation)
{
	orientation = vc_normalize(orientation);
	if (fabs(orientation.y - 1.0) < EPSILON || \
		fabs(orientation.y + 1.0) < EPSILON)
		return (1);
	return (0);
}

void	scalarize_pixels(t_scene *s)
{
	s->vp.pixel_x = vc_mult_scalar(s->camera.right_v, \
									s->vp.width / s->canvas_width);
	s->vp.pixel_y = vc_mult_scalar(s->camera.up_v, \
									-(s->vp.height / s->canvas_height));
	s->vp.pixel_init = vc_add(s->vp.up_left, \
						vc_mult_scalar(vc_add(s->vp.pixel_x, \
												s->vp.pixel_y), 0.5));
}

/*
Difference between viewport and canvas/image
-The viewport represents the virtual screen,
it does not have pixels, it is an area in 3d space
-The canvas defines how many pixels will be used to sample that viewport.
*/
void	create_viewport(t_scene *s)
{
	double		fov_to_radians;
	t_vector	worldup_v;

	worldup_v = (t_vector){0.0, 1.0, 0.0};
	if (fabs(s->camera.forward_v.y - 1) < EPSILON || \
	fabs(s->camera.forward_v.y + 1) < EPSILON)
		worldup_v = (t_vector){0.0, 0.0, 1.0};
	fov_to_radians = s->camera.fov * M_PI / 180.0;
	s->vp.width = 2.0 * tan(fov_to_radians / 2.0);
	s->vp.height = s->vp.width / (s->canvas_width / s->canvas_height);
	s->camera.right_v = vc_normalize(vc_cross_product(s->camera.forward_v, \
														worldup_v));
	s->camera.up_v = vc_normalize(vc_cross_product(s->camera.right_v, \
													s->camera.forward_v));
	s->vp.center = vc_add(s->camera.origin, \
							vc_mult_scalar(s->camera.forward_v, FOCAL_LENGTH));
	s->vp.up_left = vc_add(vc_subtract(s->vp.center, \
							vc_mult_scalar(s->camera.right_v, \
											s->vp.width / 2.0)), \
											vc_mult_scalar(s->camera.up_v, \
														s->vp.height / 2.0));
	scalarize_pixels(s);
}
