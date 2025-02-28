/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:33:59 by mrabelo-          #+#    #+#             */
/*   Updated: 2025/02/28 14:45:28 by mrabelo-         ###   ########.fr       */
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

int	ft_strcmp(char*s1, char*s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] || s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	validate_name(char*str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 3 && !ft_strcmp(str + len - 3, ".rt"))
		return (0);
	return (1);
}
