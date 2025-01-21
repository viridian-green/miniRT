/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 13:54:06 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int main(int ac, char **av)
{
	t_scene *scene;
	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	//init_mlx(scene);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return 1;
	init_scene(scene);
	parsing(av[1], scene);
}
