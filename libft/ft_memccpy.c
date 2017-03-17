/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:52:34 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/13 04:29:31 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dst;
	const char	*source;

	dst = dest;
	source = src;
	while (n > 0)
	{
		if ((*dst++ = *source++) == c)
			return (dst);
		n--;
	}
	return (NULL);
}
