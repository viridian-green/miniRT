/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:10:52 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 11:59:23 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"


int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac > 2)
		perror("Error. Please enter the config file as argument.");
	//scene.mlx_ptr = init_mlx();
	scene = ft_calloc(1, sizeof(t_scene));
	parsing(av[1], scene);
}
