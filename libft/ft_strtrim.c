/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 08:35:07 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/26 08:23:23 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
		len--;
	if (len >= i)
		return (ft_strsub(s, i, (len - i) + 1));
	else
		return (ft_strdup(""));
}
