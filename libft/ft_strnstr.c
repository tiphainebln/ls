/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 23:39:51 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/25 11:24:29 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char*)big);
	i = 0;
	j = 0;
	while (big[j] && j < n)
	{
		if (big[j] == little[i])
			i++;
		else
		{
			j = j - i;
			i = 0;
		}
		if (little[i] == '\0')
			return ((char*)&(big[j - i + 1]));
		j++;
	}
	return (NULL);
}
