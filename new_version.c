
double object_intersects(t_object object, t_ray ray, double current_t, t_scene *s)
{
    double t = INFINITY;

        ray_intersects_sp(ray, object, &t, s);
            current_t = t;
        ray_intersects_pl(ray, object, &t, s);
            current_t = t;
        ray_intersects_cy(ray, object, &t, s);
            current_t = t;

    return current_t;
}

void find_nearest_intersection(t_ray ray, t_scene *s)
{
    double closest_t = INFINITY;
    t_object *closest_object = NULL;
    t_object *current = s->object;
    double t;

    while (current)
    {
        t = object_intersects(*current, ray, closest_t, s);
        if (t > 0.001 && t < closest_t)  // Avoid self-intersections
        {
            closest_t = t;
            closest_object = current;
        }
        current = current->next;
    }

    if (closest_object)
    {
        s->intersec.t = closest_t;
        s->intersec.self = closest_object;
        // Compute the correct intersection properties only for the closest object
        // if (closest_object->type == 1) // Sphere
        ray_intersects_sp(ray, *closest_object, &closest_t, s);
        // if (closest_object->type == 2) // Plane
        ray_intersects_pl(ray, *closest_object, &closest_t, s);
        // if (closest_object->type == 3) // Cylinder
        ray_intersects_cy(ray, *closest_object, &closest_t, s);
    }
}
