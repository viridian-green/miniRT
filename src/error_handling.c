/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:40 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/01/27 14:12:54 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_exit(char *message, t_scene *scene)
{
	if (scene->mlx_ptr)
		free(scene->mlx_ptr);
	if (scene->mlx_ptr)
		free(scene->img);
	if (scene)
		free(scene);
	perror(message);
	return (EXIT_FAILURE);
}
