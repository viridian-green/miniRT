/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:15:12 by ademarti          #+#    #+#             */
/*   Updated: 2025/01/21 13:25:28 by ademarti         ###   ########.fr       */
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
    decimalPlace = 0.1;
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
            decimalPlace *= 0.1;
            str++;
        }
    }
    return (result * sign);
}

char *ft_strtok(char *str, const char *delim)
{
    static char *next_token;
    char *current_token;
    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return NULL;
    while (*next_token && ft_strchr(delim, *next_token))
        next_token++;
    if (*next_token == '\0')
        return NULL;
    current_token = next_token;
    while (*next_token && !ft_strchr(delim, *next_token))
        next_token++;
    if (*next_token)
    {
        *next_token = '\0';
        next_token++;
    }
    return current_token;
}

char *ft_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    // Move the pointer to the end of the destination string
    while (*ptr != '\0')
        ptr++;

    // Copy characters from the source string to the destination
    while (*src != '\0')
    {
        *ptr = *src;
        ptr++;
        src++;
    }

    // Null-terminate the resulting string
    *ptr = '\0';

    return dest;
}