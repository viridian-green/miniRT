/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:23 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/30 17:54:20 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

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

t_vector cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

/*
Why are we using the focal length const variable? Using a constant focal length allows for consistent control
over the camera's
*/
void create_viewport(t_scene *scene)
{
    double theta = scene->camera.fov * M_PI / 180.0;
	double viewport_width = 2.0 * FOCAL_LENGTH * tan(theta / 2.0);
    double viewport_height = viewport_width / (scene->canvas_width / scene->canvas_height);

    t_vector w = normalize(scene->camera.orientation);
    t_vector u = normalize(cross_product((t_vector){0, 1, 0}, w));
    t_vector v = cross_product(w, u);

    scene->viewport.horizontal = scalar_multiply(u, viewport_width);
     scene->viewport.vertical = scalar_multiply(v, viewport_height);
     scene->viewport.lower_left_corner = vector_subtract(
        vector_subtract(
            vector_subtract(scene->camera.viewpoint, scalar_multiply( scene->viewport.horizontal, 0.5)),
            scalar_multiply( scene->viewport.vertical, 0.5)),
        w);
}

//CHATGPT SUGGESTED FUNCTION HERE
void create_viewport(t_scene *s)
{
    double fov_to_radians;
	double d_camera_viewport;
	t_vector worldup_v;

	d_camera_viewport = 1.0;
	worldup_v = (t_vector){0.0, 1.0, 0.0};
	fov_to_radians = s->camera.fov * M_PI / 180.0;
    s->viewport.height = 2.0 * d_camera_viewport * tan(fov_to_radians / 2.0);
    s->viewport.width = s->viewport.height * (s->canvas_width / s->canvas_height);
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
*/

/*
What to ask Chatgpt -- why do we normalize the camera orientation and what does it mean?
what are the w, u and v vectors and what are they for?
Why i should implement the world up vectors,Try and figure out thanks to the different projects of the github and you
move around and what it means?


TODO: Add a world up definition and see in what ways we need it in translating
read this article https://medium.com/@iremoztimur/building-a-minirt-42-project-part-1-ae7a00aebdb9 before doing anything else!!!-
*/