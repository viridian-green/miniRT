/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:55:33 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/05 15:10:37 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trimmed;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	if (s1 == 0)
		return (ft_strdup(""));
	if (ft_strlen(s1) <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_is_in_set(s1[start], set) == 0)
		start++;
	while (ft_is_in_set(s1[end], set) == 0)
		end--;
	s1_trimmed = ft_substr(s1, start, end - start + 1);
	if (!s1_trimmed)
		return (NULL);
	i = 0;
	while (s1_trimmed[i] != '\0')
		i++;
	s1_trimmed[i] = '\0';
	return (s1_trimmed);
}
