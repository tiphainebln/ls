/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 06:10:21 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/25 08:03:16 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_strimwords(char const *s, char c)
{
	int				i;
	int				subs;

	i = 0;
	subs = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			subs++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (subs);
}

static char			*add_sub(const char *str, char c, int i)
{
	char			*sub;
	int				j;

	j = i;
	while (str[j] && str[j] != c)
		j++;
	sub = (char *)malloc(sizeof(char) * (j - i) + 1);
	j = 0;
	while (str[i] && str[i] != c)
		sub[j++] = str[i++];
	sub[j] = '\0';
	return (sub);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**str;
	int				i;
	int				j;
	int				subs;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	subs = ft_strimwords(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * subs + 1)))
		return (NULL);
	while (j < subs && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		str[j++] = add_sub(s, c, i);
		while (s[i] && s[i] != c)
			i++;
	}
	str[j] = NULL;
	return (str);
}
