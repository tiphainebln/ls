/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:58:55 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/23 02:34:57 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	if (!(str = ft_strnew(ft_intlen(n))))
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		str[i++] = '-';
	}
	while (n / ret > 9)
		ret = ret * 10;
	while (ret)
	{
		str[i++] = (n / ret) + 48;
		n = n % ret;
		ret = ret / 10;
	}
	str[i] = '\0';
	return (str);
}
