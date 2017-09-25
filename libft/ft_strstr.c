/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 00:51:22 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/15 02:57:49 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && little[j])
				j++;
			tmp = (char *)&big[i];
			if (little[j] == '\0')
				return (tmp);
		}
		i++;
	}
	return (NULL);
}
