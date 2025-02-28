/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:22:56 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/28 14:23:10 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_ambience(char *line, t_scene *scene, int *counts)
{
	if (counts[0] >= 1)
		free_exit("Error. Multiple ambience definitions.\n", scene, 1);
	counts[0]++;
	parse_ambience(line, scene);
}

void	handle_camera(char *line, t_scene *scene, int *counts)
{
	if (counts[1] >= 1)
		free_exit("Error. Multiple camera definitions.\n", scene, 1);
	counts[1]++;
	parse_camera(line, scene);
}

void	handle_light(char *line, t_scene *scene, int *counts)
{
	if (counts[2] >= 1)
		free_exit("Error. Multiple light definitions.\n", scene, 1);
	counts[2]++;
	parse_light(line, scene);
}
