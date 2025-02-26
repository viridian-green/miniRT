double find_discriminant(t_results result , t_vector dir_perp , \
	t_ray r, t_object object)
{
    t_vector axis;   // Ensure axis is normalized
    double radius;   // Radius of the cylinder
    double dot_dir_axis;
    double dot_oc_axis;
	t_vector top_cap;
	t_vector oc_perp;
	double c;

	result.oc = vc_subtract(r.origin, object.cy.center);
	axis = vc_normalize(object.cy.orientation);
	radius = object.cy.diameter / 2.0;
	dot_dir_axis = vc_dot(r.direction, axis);
	dot_oc_axis = vc_dot(result.oc, axis);
    top_cap = vc_add(object.cy.center, vc_mult_scalar(axis, object.cy.height / 2.0));
	oc_perp = vc_subtract(result.oc, vc_mult_scalar(axis, dot_oc_axis));
    dir_perp = vc_subtract(r.direction, vc_mult_scalar(axis, dot_dir_axis));
	result.a = vc_dot(dir_perp, dir_perp);
    result.b = 2.0 * vc_dot(oc_perp, dir_perp);
    c = vc_dot(oc_perp, oc_perp) - radius * radius;
	return (result.b * result.b - 4.0 * result.a * c);
}
// void cyl_side_is_closest(double t_cap, double t_cyl_side, double *t, t_object *object)
// {
// 	double radius;
// 	t_vector axis;
// 	axis = vc_normalize(object->cy.orientation);
// 	radius = object->cy.diameter / 2.0;

// 	if (t_cyl_side >= 0.0 && (t_cap < 0.0 || t_cyl_side < t_cap))
//     {
//         *t = t_cyl_side;
//         object->intersec->t = *t;
//         object->intersec->point = vectorize_t(object->ray, *t);
//         object->intersec->normal = vc_normalize(vc_subtract(object->intersec->point, object->cy.center));
//         object->intersec->color = object->cy.color;
//     }
// }


void cyl_cap_is_closest(t_results result, t_object *object,  double *t,  t_scene *s)
{
	double radius;
	t_vector axis = vc_normalize(object->cy.orientation);
	radius = object->cy.diameter / 2.0;
    if (result.t_cap >= 0.0)
    {
        *t = result.t_cap;
        s->intersec.t = *t;
        s->intersec.point = vectorize_t(s->ray, *t);
        s->intersec.normal = axis;
        if (vc_dot(s->ray.direction, axis) > 0.0)
			s->intersec.normal = vc_mult_scalar(axis, -1.0); // Flip normal if hitting from inside
		s->intersec.color = object->cy.color;
    }
	else if (result.t_cyl_side >= 0.0 && (result.t_cap < 0.0 || result.t_cyl_side < result.t_cap))
    {
        *t = result.t_cyl_side;
        s->intersec.t = *t;
        s->intersec.point = vectorize_t(object->ray, *t);
        s->intersec.normal = vc_normalize(vc_subtract(s->intersec.point, object->cy.center));
        s->intersec.color = object->cy.color;
    }
}

void find_t1(t_results result, double sqrt_discriminant, double t_cylinder, t_object object)
{
	double a;
	double t1;
	t_vector axis;
	t_vector dir_perp;
	double dot_dir_axis;
	t_vector intersection1;
	double height1;

	axis = vc_normalize(object.cy.orientation);
	dot_dir_axis = vc_dot(object.ray.direction, axis);
	dir_perp = vc_subtract(object.ray.direction, vc_mult_scalar(axis, dot_dir_axis));
	a = vc_dot(dir_perp, dir_perp);

	t1 = (-result.b - sqrt_discriminant) / (2.0 * a);
    if (t1 >= 0.0)
    {
        intersection1 = vc_add(object.ray.origin, vc_mult_scalar(object.ray.direction, t1));
        height1 = vc_dot(vc_subtract(intersection1, object.cy.center), axis);
        if (height1 >= -object.cy.height / 2.0 && height1 <= object.cy.height / 2.0)
            t_cylinder = t1;
}
}
void find_t2(t_results result, double sqrt_discriminant, double t_cylinder, t_object object)
{
	double a;
	double t2;
	t_vector axis;
	t_vector dir_perp;
	double dot_dir_axis;
	t_vector intersection2;
	double height2;

	axis = vc_normalize(object.cy.orientation);
	dot_dir_axis = vc_dot(object.ray.direction, axis);
	dir_perp = vc_subtract(object.ray.direction, vc_mult_scalar(axis, dot_dir_axis));
	a = vc_dot(dir_perp, dir_perp);
	t2 = (-result.b + sqrt_discriminant) / (2.0 * a);
	if (t2 >= 0.0)
	{
		intersection2 = vc_add(object.ray.origin, vc_mult_scalar(object.ray.direction, t2));
		height2 = vc_dot(vc_subtract(intersection2, object.cy.center), axis);
		if (height2 >= -object.cy.height / 2.0 && height2 <= object.cy.height / 2.0)
		{
			if (t_cylinder < 0.0 || t2 < t_cylinder)
				t_cylinder = t2;
		}
	}
}

int ray_intersects_cy(t_ray r, t_object object, double *t, t_scene *s)
{
	t_results result;
	t_vector axis;
	t_vector bottom_cap;
	t_vector top_cap;
	double sqrt_discriminant;
	double radius;


	result.oc = vc_subtract(r.origin, object.cy.center);
	axis = vc_normalize(object.cy.orientation);
    bottom_cap = vc_subtract(object.cy.center, vc_mult_scalar(axis, object.cy.height / 2.0));
    top_cap = vc_add(object.cy.center, vc_mult_scalar(axis, object.cy.height / 2.0));
	result.discriminant = find_discriminant(result, bottom_cap, r, object);
	sqrt_discriminant = sqrt(result.discriminant);
	radius = object.cy.diameter / 2.0;
	result.t_cyl_side = -1.0;
	result.t_cylinder =-1.0;
	result.t_cap = -1.0;

	if (result.discriminant >= 0.0)
	{
	find_t1(result, sqrt_discriminant, result.t_cylinder, object);
	find_t2(result, sqrt_discriminant, result.t_cylinder,object);
	}
    // Check for intersections with the caps
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
                if (result.t_cap < 0.0 || t_plane < result.t_cap)
				result.t_cap = t_plane;
            }
        }
	}
	cyl_cap_is_closest(result, &object, t, s);
	return 0;
}

typedef struct {
    double a;
    double b;
    double t_cylinder;
	double t_cap;
	double t_cyl_side;
	t_vector oc;
	t_vector dir_perp;
	double discriminant;
} t_results;
