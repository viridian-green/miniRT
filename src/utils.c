/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:15:12 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/20 14:43:40 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double process_integer_part(const char **str)
{
    double result;

	result = 0.0;
    while (ft_isdigit(**str))
	{
        result = result * 10 + (**str - '0');
        (*str)++;
    }
    return (result);
}

double ft_atof(const char *str)
{
	double result;
	double decimalPlace;
	int sign;

	result = 0.0;
	decimalPlace = 1.0;
	sign = 1;
    if (*str == '-')
	{
        sign = -1;
        str++;
    }
    result = process_integer_part(&str);
    if (*str == '.') {
        str++;
        while (ft_isdigit(*str))
		{
            result += (*str - '0') * decimalPlace;
            decimalPlace *= 0.1;
            str++;
        }
    }
    return (result * sign);
}