/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:23 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/13 17:48:26 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Check if the camera orientation is aligned with world-up or its negative
*/
int	is_aligned_with_up_vector(t_vector orientation)
{
	orientation = normalize(orientation);
	if (fabs(orientation.y - 1.0) < EPSILON || \
		fabs(orientation.y + 1.0) < EPSILON)
		return (1);
	return (0);
}

void scalarize_pixels(t_scene *s)
{
	s->vp.pixel_x = vc_mult_scalar(s->camera.right_v, s->vp.width / s->canvas_width);
    s->vp.pixel_y = vc_mult_scalar(s->camera.up_v, -(s->vp.height / s->canvas_height));
}


/*
Difference between viewport and canvas/image
-The viewport represents the virtual screen, it does not have pixels, it is an area in 3d space
-The canvas defines how many pixels will be used to sample that viewport.
*/
void	create_viewport(t_scene *s)
{
	double		fov_to_radians;
	double		d_camera_viewport;
	t_vector	worldup_v;

	d_camera_viewport = 1.0;
	worldup_v = (t_vector){0.0, 1.0, 0.0};
	fov_to_radians = s->camera.fov * M_PI / 180.0;
	s->vp.width = 2.0 * tan(fov_to_radians / 2.0);
	s->vp.height = s->vp.width * (s->canvas_width / s->canvas_height);
	if (!is_aligned_with_up_vector(s->camera.forward_v))
		s->camera.right_v = normalize(cross_product(worldup_v, s->camera.forward_v));
	else
		s->camera.right_v = normalize(cross_product((t_vector){0.0, 0.0, 1.0}, s->camera.forward_v));
	s->camera.up_v = cross_product(s->camera.forward_v, s->camera.right_v);
	scalarize_pixels(s);
}

/*
TODO: Add the pixel calculations later
    // s->vp.pixel00 = vector_add(s->vp.up_left,
    // scalar_multiply(vector_add(s->vp.pixel_x, s->vp.pixel_y), 0.5))
TODO: Add a world up definition and see in what ways we need it in translating
read this article https://medium.com/@iremoztimur/building-a-minirt-42-project-part-1-ae7a00aebdb9 before doing anything else!!!-
*/

