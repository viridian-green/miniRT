/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:40 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/22 17:37:26 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_linked_list(t_object *object)
{
	t_object	*tmp;

	while (object)
	{
		tmp = object->next;
		free(object);
		object = tmp;
	}
}

int	is_in_linked_list(t_object *head, t_object *target)
{
	while (head)
	{
		if (head == target)
			return (1);
		head = head->next;
	}
	return (0);
}

int	free_exit(char *message, t_scene *scene)
{
	if (scene)
	{
		if (scene->img)
			mlx_delete_image(scene->mlx_ptr, scene->img);
		if (scene->mlx_ptr)
			mlx_terminate(scene->mlx_ptr);
		if (scene->object)
			free_linked_list(scene->object);
		if (scene->intersec.self && \
			!is_in_linked_list(scene->object, scene->intersec.self))
		{
			free(scene->intersec.self);
			scene->intersec.self = NULL;
		}
		free(scene);
		scene = NULL;
	}
	printf("%s", message);
	exit (0);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	handle_parse_error(char **split_line, t_scene *scene, char *message)
{
	if (split_line)
		free_split(split_line);
	free_exit(message, scene);
}
