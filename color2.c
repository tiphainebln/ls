/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 04:20:49 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/24 05:43:39 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_putlnk(void)
{
	ft_putstr("\033[35m");
	return (0);
}

int		ft_putreg(void)
{
	ft_putstr("\033[36m");
	return (0);
}

int		ft_putsoc(void)
{
	ft_putstr("\033[37m");
	return (0);
}

int		ft_putwat(void)
{
	ft_putstr("\033[38m");
	return (0);
}
