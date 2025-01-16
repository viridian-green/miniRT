/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:19:38 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/07 13:15:28 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (p_dest > p_src)
	{
		while (n--)
		{
			p_dest[n] = p_src[n];
		}
	}
	else if (p_dest < p_src)
		ft_memcpy(dest, src, n);
	return (dest);
}
