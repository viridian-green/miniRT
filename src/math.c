/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:45:00 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/17 16:11:21 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_vector	vc_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	vc_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	vc_mult_scalar(t_vector v, double scalar)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

double vec_dot(t_vector v1, t_vector v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/*
This step ensures the right_v is always perpendicular to forward_v, no matter
where the camera is looking. Finally, we compute  v, the true "up" direction
for the camera, by taking the cross product of v and w. This guarantees that
v is perpendicular to both w and u, forming a correct 3D basis.
By using cross products, we make sure that the camera's local coordinate
system is always orthonormal and properly aligned to the scene!
*/
t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

//why float? could it be double?
float	vc_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vectorize_t(t_ray r, double t)
{
	return (vc_add(r.origin, vc_mult_scalar(r.direction, t)));
}

//We make the vecor's magnitude (size) equal to 1.
t_vector	normalize(t_vector v)
{
	t_vector	norm;
	float		len;

	len = vc_length(v);
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}
