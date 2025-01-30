/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:23 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/30 19:23:20 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

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
This step ensures the right_v is always perpendicular to forward_v, no matter where the camera is looking. Finally, we compute  v, the true "up" direction for the camera, by taking the cross product of v and w. This guarantees that v is perpendicular to both w and u, forming a correct 3D basis.
By using cross products, we make sure that the camera's local coordinate system is always orthonormal and properly aligned to the scene!
*/
t_vector cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}
/*
Check if the camera orientation is aligned with world-up or its negative
*/
int is_aligned_with_up_vector(t_vector orientation)
{
    orientation = normalize(orientation);
    if (fabs(orientation.y - 1.0) < EPSILON || fabs(orientation.y + 1.0) < EPSILON)
        return 1;
    return 0;
}

void create_viewport(t_scene *s)
{
    double fov_to_radians;
	double d_camera_viewport;
	t_vector worldup_v;

	d_camera_viewport = 1.0;
	worldup_v = (t_vector){0.0, 1.0, 0.0};
	fov_to_radians = s->camera.fov * M_PI / 180.0;
    s->vp.height = 2.0 * d_camera_viewport * tan(fov_to_radians / 2.0);
    s->vp.width = s->vp.height * (s->canvas_width / s->canvas_height);
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

