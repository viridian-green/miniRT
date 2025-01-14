#include "minirt.h"
#include <fcntl.h>
#include "minilibx-linux/mlx_int.h"
#include "minilibx-linus/mlx.h"

int parse_map(char *config_file)
{
	int	fd;

	if (fd < 0)
		perror("Error. Cannot open file.");
	fd = open(config_file, O_RDONLY);
	close(fd);
}

void init_mlx(t_scene scene)
{
	scene.mlx_ptr = mlx_init();
}

int main(int ac, char **av)
{
	t_scene scene;
	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	init_mlx(scene);
	parse_map(av[1]);
}