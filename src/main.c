/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/14 15:53:29 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
void init_mlx(t_scene *scene)
{
	scene->mlx_ptr = mlx_init();
}
*/

int main(int ac, char **av)
{
	t_scene scene;
	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	//init_mlx(scene);
	parsing(av[1], &scene);
}