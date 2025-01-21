#include "minirt.h"

void init_ambience_camera(t_ambience *ambience, t_camera *camera)
{
	ambience->light_ratio = 0;
	ambience->color.r = 0;
	ambience->color.g = 0;
	ambience->color.b = 0;
	camera->viewpoint.x = 0;
	camera->viewpoint.y = 0;
	camera->viewpoint.z = 0;
	camera->orientation.x = 0;
	camera->orientation.y = 0;
	camera->orientation.z = 0;
}

void init_light_sphere(t_light *light, t_sp *sp)
{
	light->light_point.x = 0;
	light->light_point.y = 0;
	light->light_point.z = 0;
	light->diameter = 0;
	light->color.r = 0;
	light->color.g = 0;
	light->color.b = 0;
	sp->center.x = 0;
    sp->center.y = 0;
    sp->center.z = 0;
    sp->diameter = 0;
    sp->color.r = 0;
    sp->color.g = 0;
    sp->color.b = 0;
}

void init_plane(t_pl *pl) {
    pl->plane_point.x = 0;
    pl->plane_point.y = 0;
    pl->plane_point.z = 0;
    pl->normal_vector.x = 0;
    pl->normal_vector.y = 0;
    pl->normal_vector.z = 0;
    pl->color.r = 0;
    pl->color.g = 0;
    pl->color.b = 0;
}

void init_cylinder(t_cy *cy) {
    cy->center.x = 0;
    cy->center.y = 0;
    cy->center.z = 0;
    cy->axis.x = 0;
    cy->axis.y = 0;
    cy->axis.z = 0;
    cy->diameter = 0;
    cy->height = 0;
    cy->color.r = 0;
    cy->color.g = 0;
    cy->color.b = 0;
}

void init_scene(t_scene *scene)
{
	init_ambience_camera(&scene->ambience, &scene->camera);
	init_light_sphere(&scene->light, &scene->sp);
	init_cylinder(&scene->cy);
	init_plane(&scene->pl);
}