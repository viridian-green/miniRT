/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:40 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/03 18:47:54 by mrabelo-         ###   ########.fr       */
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
	exit (EXIT_FAILURE);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	handle_parse_error(char **split_line, t_scene *scene, char *message)
{
	if (split_line)
		free_split(split_line);
	free_exit(message, scene);
}
