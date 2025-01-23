/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:23 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/23 19:27:46 by ademarti         ###   ########.fr       */
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
void create_viewport(t_scene *scene)
{
    double theta = scene->camera.fov * M_PI / 180.0;
    double viewport_width = 2.0 * FOCAL_LENGTH * tan(theta / 2.0);
    double viewport_height = viewport_width / (scene->canvas_width / scene->canvas_height);

    t_vector world_up = {0.0, 1.0, 0.0};
    if (fabs(scene->camera.orientation.y - 1) < EPSILON || fabs(scene->camera.orientation.y + 1) < EPSILON)
        world_up = (t_vector){0.0, 0.0, 1.0};

    t_vector w = normalize(scene->camera.orientation);
    t_vector u = normalize(cross_product(world_up, w));
    t_vector v = cross_product(w, u);

    scene->viewport.width = viewport_width;
    scene->viewport.height = viewport_height;
    scene->viewport.horizontal = scalar_multiply(u, viewport_width);
    scene->viewport.vertical = scalar_multiply(v, viewport_height);

    scene->viewport.center = vector_add(scene->camera.viewpoint, scalar_multiply(w, FOCAL_LENGTH));

    scene->viewport.up_left = vector_add(
        vector_subtract(scene->viewport.center, scalar_multiply(scene->viewport.horizontal, 0.5)),
        scalar_multiply(scene->viewport.vertical, 0.5));

    scene->viewport.pixel_x = scalar_multiply(u, viewport_width / scene->canvas_width);
    scene->viewport.pixel_y = scalar_multiply(v, -(viewport_height / scene->canvas_height));

    scene->viewport.pixel00 = vector_add(scene->viewport.up_left,
        scalar_multiply(vector_add(scene->viewport.pixel_x, scene->viewport.pixel_y), 0.5));

    scene->camera.right = u;
    scene->camera.up = v;
}

What to ask Chatgpt -- why do we normalize the camera orientation and what does it mean?
what are the w, u and v vectors and what are they for?
Why i should implement the world up vectors,Try and figure out thanks to the different projects of the github and you
move around and what it means?


TODO: Add a world up definition and see in what ways we need it in translating
read this article https://medium.com/@iremoztimur/building-a-minirt-42-project-part-1-ae7a00aebdb9 before doing anything else!!!