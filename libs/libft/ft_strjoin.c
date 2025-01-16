/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:43:30 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/05 15:50:32 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstring;
	size_t	len_s1_s2;
	size_t	i;
	size_t	j;

	len_s1_s2 = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newstring = (char *)malloc(sizeof(char) * (len_s1_s2 + 1));
	if (!newstring)
		return (NULL);
	while (s1[i] != '\0')
	{
		newstring[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstring[i + j] = s2[j];
		j++;
	}
	newstring[i + j] = '\0';
	return (newstring);
}
