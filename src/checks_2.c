/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:33:59 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/25 16:34:47 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_format(char **split_line, int expected_params)
{
	int	i;

	i = 0;
	while (split_line[i] != NULL)
		i++;
	if (i != expected_params)
		return (1);
	return (0);
}

int	validate_numeric_value(char *str)
{
	int	i;

	i = 0;
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (1);
		i++;
	}
	return (0);
}
