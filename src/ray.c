		/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:21 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/22 17:50:52 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/*In this function the pixels are scaled both vertically and horizontally
The variable p_center (pixel center) marks the exact spot on the window in 3D space for a given pixel (from 2D to 3D)
*/
t_ray	create_ray(double p_x, double p_y, t_vector origin, t_scene *scene)
{
	t_ray		ray;
	t_vector	p_center;
	t_vector	p_x_sc;
	t_vector	p_y_sc;

	p_x_sc = vc_mult_scalar(scene->vp.pixel_x, p_x);
	p_y_sc = vc_mult_scalar(scene->vp.pixel_y, p_y);
	p_center = vc_add(vc_add(scene->vp.pixel_init, p_x_sc), p_y_sc);
	ray.origin = origin;
	ray.direction = vc_subtract(p_center, origin);
	return (ray);
}

double	ray_intersects_sp(t_ray ray, t_object object, double *t, t_scene *s)
{
	t_vector	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	oc = vc_subtract(ray.origin, object.sp.center);
	a = vc_dot(ray.direction, ray.direction);
	half_b = vc_dot(oc, ray.direction);
	c = vc_dot(oc, oc) - object.sp.diameter * object.sp.diameter / 4;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	else
	{
		*t = ((-half_b - sqrt(discriminant)) / a);
		s->intersec.t = *t;
		s->intersec.point = vectorize_t(ray, *t);
		s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object.sp.center));
		s->intersec.color = object.sp.color;
	}
	return (1);
}

int ray_intersects_pl(t_ray ray, t_object object, double *t, t_scene *s)
{
    // The plane's normal is its orientation
    t_vector normal = object.pl.orientation;

    // Calculate the denominator (dot product between ray direction and plane normal)
    double denom = vc_dot(ray.direction, normal);

    if (fabs(denom) > 1e-6)  // Avoid division by zero
    {
        // Vector from ray origin to a point on the plane
        t_vector oc = vc_subtract(ray.origin, object.pl.plane_point);

        // Calculate the intersection point distance
        *t = -vc_dot(oc, normal) / denom;

        if (*t >= 0.0)  // Check if intersection is in front of the ray
        {
            s->intersec.t = *t;
            s->intersec.point = vectorize_t(ray, *t);  // Compute intersection point
            s->intersec.normal = normal;;  // Plane normal (already normalized)
            s->intersec.color = object.pl.color;  // Store color
            return 1;  // Ray intersects the plane
        }
    }
    return 0;  // No intersection
}

double find_discriminant(t_vector oc_perp , t_vector dir_perp , \
	double radius, double a)
{
    double b = 2.0 * vc_dot(oc_perp, dir_perp);
    double c = vc_dot(oc_perp, oc_perp) - radius * radius;

	return (b * b - 4.0 * a * c);
}

int cyl_side_is_closest(double t_cap, double t_cyl_side, double *t, t_scene *s)
{
	double radius;

	radius = s->object->cy.diameter / 2.0;
	if (t_cyl_side >= 0.0 && (t_cap < 0.0 || t_cyl_side < t_cap))
    {
        *t = t_cyl_side;
        s->intersec.t = *t;
        s->intersec.point = vectorize_t(s->ray, *t);
        s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, s->object->cy.center));
        s->intersec.color = s->object->cy.color;
        return 1;
    }
	else
		return 0;
}

int cyl_cap_is_closest(double t_cap, t_vector axis,  double *t, t_scene *s)
{
	double radius;

	radius = s->object->cy.diameter / 2.0;
    if (t_cap >= 0.0)
    {
        *t = t_cap;
        s->intersec.t = *t;
        s->intersec.point = vectorize_t(s->ray, *t);
        s->intersec.normal = axis;
        if (vc_dot(s->ray.direction, axis) > 0.0)
            s->intersec.normal = vc_mult_scalar(axis, -1.0); // Flip normal if hitting from inside
        s->intersec.color = s->object->cy.color;
        return 1;
    }
	else
		return 0;
}

int ray_intersects_cy(t_ray r, t_object object, double *t, t_scene *s)
{
    t_vector oc; // Vector from ray origin to cylinder center
    t_vector axis;   // Ensure axis is normalized
    double radius;   // Radius of the cylinder
    double dot_dir_axis;
    double dot_oc_axis;
	double discriminant;
	t_vector bottom_cap;
	t_vector top_cap;
	t_vector oc_perp;
	t_vector dir_perp;
	double a;
	double b;

	oc = vc_subtract(r.origin, object.cy.center);
	axis = vc_normalize(object.cy.orientation);
	radius = object.cy.diameter / 2.0;
	dot_dir_axis = vc_dot(r.direction, axis);
	dot_oc_axis = vc_dot(oc, axis);
    bottom_cap = vc_subtract(object.cy.center, vc_mult_scalar(axis, object.cy.height / 2.0));
    top_cap = vc_add(object.cy.center, vc_mult_scalar(axis, object.cy.height / 2.0));
	oc_perp = vc_subtract(oc, vc_mult_scalar(axis, dot_oc_axis));  // Vector perpendicular to axis
    dir_perp = vc_subtract(r.direction, vc_mult_scalar(axis, dot_dir_axis));

    // Now form the quadratic equation to solve for intersection t
      // Ray direction perpendicular to axis
	a = vc_dot(dir_perp, dir_perp);  // Coefficient for quadratic equation
    b = 2.0 * vc_dot(oc_perp, dir_perp);
	discriminant = find_discriminant(oc_perp, dir_perp, radius, a);
    double t_cyl_side = -1.0;

    if (discriminant >= 0.0)
    {
        // Calculate t values for the intersection
        double sqrt_discriminant = sqrt(discriminant);
        double t1 = (-b - sqrt_discriminant) / (2.0 * a);
        double t2 = (-b + sqrt_discriminant) / (2.0 * a);

        // Check if t1 is valid and within the cylinder's height
        if (t1 >= 0.0)
        {
            t_vector intersection1 = vc_add(r.origin, vc_mult_scalar(r.direction, t1));
            double height1 = vc_dot(vc_subtract(intersection1, object.cy.center), axis);
            if (height1 >= -object.cy.height / 2.0 && height1 <= object.cy.height / 2.0)
            {
                t_cyl_side = t1;
            }
        }

        // Check if t2 is valid and within the cylinder's height
        if (t2 >= 0.0)
        {
            t_vector intersection2 = vc_add(r.origin, vc_mult_scalar(r.direction, t2));
            double height2 = vc_dot(vc_subtract(intersection2, object.cy.center), axis);
            if (height2 >= -object.cy.height / 2.0 && height2 <= object.cy.height / 2.0)
            {
                if (t_cyl_side < 0.0 || t2 < t_cyl_side)
                    t_cyl_side = t2;
            }
        }
    }

    // Check for intersections with the caps
    double t_cap = -1.0;
    for (int i = 0; i < 2; i++)
    {
        t_vector cap_center;
        if (i == 0)
            cap_center = bottom_cap;
        else
            cap_center = top_cap;

        double t_plane = vc_dot(vc_subtract(cap_center, r.origin), axis) / vc_dot(r.direction, axis);
        if (t_plane >= 0.0)
        {
            t_vector p = vc_add(r.origin, vc_mult_scalar(r.direction, t_plane));
            if (vc_length(vc_subtract(p, cap_center)) <= radius)
            {
                if (t_cap < 0.0 || t_plane < t_cap)
                    t_cap = t_plane;
            }
        }
    }

	cyl_side_is_closest(t_cap, t_cyl_side, t, s);
	cyl_cap_is_closest(t_cap, axis, t, s);

    return 0;
}