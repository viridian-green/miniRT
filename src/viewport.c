/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:23 by ademarti          #+#    #+#             */
/*   Updated: 2025/02/05 14:16:39 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//We make the vecor's magnitude (size) equal to 1.
t_vector	normalize(t_vector v)
{
	t_vector	norm;
	float		len;

	len = vector_length(v);
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

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

void	create_viewport(t_scene *s)
{
	double		fov_to_radians;
	double		d_camera_viewport;
	t_vector	worldup_v;

	d_camera_viewport = 1.0;
	worldup_v = (t_vector){0.0, 1.0, 0.0};
	fov_to_radians = s->camera.fov * M_PI / 180.0;
	s->vp.height = 2.0 * d_camera_viewport * tan(fov_to_radians / 2.0);
	s->vp.width = s->vp.height * (s->vp.width / s->vp.height);
	if (!is_aligned_with_up_vector(s->camera.forward_v))
		s->camera.right_v = normalize(cross_product(worldup_v, s->camera.forward_v));
	else
		s->camera.right_v = normalize(cross_product((t_vector){0.0, 0.0, 1.0}, s->camera.forward_v));
	s->camera.up_v = cross_product(s->camera.forward_v, s->camera.right_v);
}

/*
TODO: Add the pixel calculations later
scene->viewport.pixel_x = scalar_multiply(u, viewport_width / scene->canvas_width);
    scene->viewport.pixel_y = scalar_multiply(v, -(viewport_height / scene->canvas_height));

    scene->viewport.pixel00 = vector_add(scene->viewport.up_left,
        scalar_multiply(vector_add(scene->viewport.pixel_x, scene->viewport.pixel_y), 0.5));

Why are we using the focal length const variable? Using a constant focal length allows for consistent control
over the camera's
TODO: Add a world up definition and see in what ways we need it in translating
read this article https://medium.com/@iremoztimur/building-a-minirt-42-project-part-1-ae7a00aebdb9 before doing anything else!!!-
*/

