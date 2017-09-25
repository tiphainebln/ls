/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:55:03 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/14 11:09:38 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*ptr_dest;
	size_t			i;

	ptr_dest = (char *)dest;
	if (ptr_dest < (char *)src)
	{
		i = 0;
		while (n != i)
		{
			*(ptr_dest + i) = *((char *)src + i);
			++i;
		}
	}
	else
		while (n != 0)
		{
			--n;
			*(ptr_dest + n) = *((char *)src + n);
		}
	return (dest);
}
