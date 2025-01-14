#include "minirt.h"
#include <fcntl.h>

int parse_map(char *config_file)
{
	int	fd;

	if (fd < 0)
		perror("Error. Cannot open file.");

	fd = open(config_file, O_RDONLY);
}


int main(int ac, char **av)
{
	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	parse_map(av[1]);
}