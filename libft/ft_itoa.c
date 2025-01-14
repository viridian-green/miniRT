/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:07:41 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/30 15:50:19 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_of_int(long n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
	{
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*m_alloc(int n)
{
	char	*result;
	size_t	int_len;
	long	nbr;

	nbr = n;
	int_len = size_of_int(nbr);
	result = (char *)malloc(sizeof(char) * (int_len + 1));
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*result;
	long	nbr;
	size_t	int_len;

	nbr = n;
	int_len = size_of_int(nbr);
	i = int_len - 1;
	result = m_alloc(n);
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		result[i] = ((nbr % 10) + 48);
	while (nbr != 0)
	{
		result[i] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		i--;
	}
	result[int_len] = '\0';
	return (result);
}
