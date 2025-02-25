/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:04:37 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/25 16:01:37 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*new_object_node(void)
{
	t_object	*node;

	node = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

void	add_node_to_object(t_object **head, t_object *node)
{
	t_object	*temp;

	if (head)
	{
		if (!*head)
			*head = node;
		else
		{
			temp = *head;
			while (temp->next)
				temp = temp->next;
			temp->next = node;
		}
	}
}

void	parse_sphere(char *line, t_scene *scene)
{
	char		**split_line;
	t_object	*node;

	split_line = ft_split(line, ' ');
	if (!split_line || validate_line_format(split_line, 4))
		handle_parse_error(split_line, scene, "Error. Invalid sphere format.");
	node = new_object_node();
	if (!node)
		handle_parse_error(split_line, scene, "Error. Memory allocation failed.");
	add_node_to_object(&scene->object, node);
	set_coordinates(&split_line[0], &node->sp.center);
	if (validate_numeric_value(split_line[2]))
		handle_parse_error(split_line, scene, "Error. Invalid sphere diameter.");
	node->sp.diameter = ft_atof(split_line[2]);
	set_color(&split_line[3], &node->sp.color);
	if (validate_diameter(node->sp.diameter) || validate_color(&node->sp.color))
		handle_parse_error(split_line, scene, "Error. Invalid sphere parameters.");
	node->type = 1;
	free_split(split_line);
}

void	parse_plane(char *line, t_scene *scene)
{
	char		**split_line;
	t_object	*node;

	split_line = ft_split(line, ' ');
	if (!split_line || validate_line_format(split_line, 4))
		handle_parse_error(split_line, scene, "Error. Invalid plane format.");
	node = new_object_node();
	if (!node)
		handle_parse_error(split_line, scene, "Error. Memory allocation failed.");
	add_node_to_object(&scene->object, node);
	set_coordinates(&split_line[0], &node->pl.plane_point);
	set_orientation(&split_line[1], &node->pl.orientation);
	set_color(&split_line[3], &node->pl.color);
	if (validate_orientation(&node->pl.orientation) || \
		validate_color(&node->pl.color))
		handle_parse_error(split_line, scene, "Error. Invalid plane parameters.");
	node->type = 2;
	free_split(split_line);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	char		**split_line;
	t_object	*node;

	split_line = ft_split(line, ' ');
	if (!split_line || validate_line_format(split_line, 6))
		handle_parse_error(split_line, scene, "Error. Invalid cylinder format.");
	node = new_object_node();
	if (!node)
		handle_parse_error(split_line, scene, "Error. Memory allocation failed.");
	add_node_to_object(&scene->object, node);
	set_coordinates(&split_line[0], &node->cy.center);
	set_orientation(&split_line[1], &node->cy.orientation);
	if (validate_numeric_value(split_line[3]) || \
		validate_numeric_value(split_line[4]))
		handle_parse_error(split_line, scene, "Error. Invalid cylinder dimensions.");
	node->cy.diameter = ft_atof(split_line[3]);
	node->cy.height = ft_atof(split_line[4]);
	set_color(&split_line[5], &node->cy.color);
	if (validate_orientation(&node->cy.orientation) || \
		validate_diameter(node->cy.diameter) || \
		validate_height(node->cy.height) || \
		validate_color(&node->cy.color))
		handle_parse_error(split_line, scene, "Error. Invalid cylinder parameters.");
	node->type = 3;
	free_split(split_line);
}
