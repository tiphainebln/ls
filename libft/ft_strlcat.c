/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:48:03 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/25 08:29:00 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t size_dst;
	size_t size_src;
	size_t total_size;
	size_t i;

	size_dst = ft_strlen(dest);
	size_src = ft_strlen(src);
	total_size = size_dst + size_src;
	i = 0;
	while (src[i] && size_dst < size - 1 && size != 0)
		dest[size_dst++] = src[i++];
	dest[size_dst] = '\0';
	if (size < total_size - size_src)
		return (size + size_src);
	return (total_size);
}
