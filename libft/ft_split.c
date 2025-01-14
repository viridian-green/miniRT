/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:13:24 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/12 15:02:38 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && x == 0)
		{
			x = 1;
			word_count++;
		}
		else if (s[i] == c)
			x = 0;
		i++;
	}
	return (word_count);
}

static void	ft_free(char **result, size_t occurences)
{
	size_t	i;

	i = 0;
	while (i < occurences)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char	**make_substrings(char const *s, char c, char **result)
{
	size_t	i;
	size_t	start;
	size_t	j;

	i = 0;
	start = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
			{
				i++;
			}
			result[j] = ft_substr(s, start, i - start);
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	occurences;

	occurences = count_words(s, c);
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (occurences + 1));
	if (!result)
	{
		ft_free(result, occurences);
		return (NULL);
	}
	make_substrings(s, c, result);
	return (result);
}
