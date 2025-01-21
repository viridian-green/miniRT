/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:15:12 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 13:13:47 by ademarti         ###   ########.fr       */
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
    return result;
}

double ft_atof(const char *str)
{
    double result;
    double decimalPlace;
    int sign;

    result = 0.0;
    decimalPlace = 0.1; // Start at 0.1 for the fractional part
    sign = 1;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    result = process_integer_part(&str);

    if (*str == '.')
    {
        str++;
        while (ft_isdigit(*str))
        {
            result += (*str - '0') * decimalPlace;
            decimalPlace *= 0.1; // Move to the next decimal position
            str++;
        }
    }

    return result * sign;
}