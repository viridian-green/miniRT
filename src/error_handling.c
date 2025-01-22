#include "minirt.h"

int free_exit(char *message, t_scene *scene)
{
	if (scene->mlx_ptr)
		free(scene->mlx_ptr);
	if (scene->mlx_ptr)
		free(scene->img);
	if (scene)
		free(scene);
	perror(message);
	return EXIT_FAILURE;
}