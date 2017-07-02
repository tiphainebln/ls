/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 07:06:47 by tbouline          #+#    #+#             */
/*   Updated: 2016/12/31 05:01:38 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str3join(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) \
		+ ft_strlen(s3) + 1));
	if (str)
	{
		while (s1[++i])
			str[i] = s1[i];
		while (s2[j])
			str[i++] = s2[j++];
		j = 0;
		while (s3[j])
			str[i++] = s3[j++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str)
	{
		while (s1[++i])
			str[i] = s1[i];
		while (s2[j])
			str[i++] = s2[j++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
