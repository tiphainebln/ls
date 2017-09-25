/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 04:20:33 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/24 05:41:56 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		init_tab(int (*tab[13])(void))
{
	tab[6] = &ft_putblk;
	tab[2] = &ft_putchr;
	tab[4] = &ft_putdir;
	tab[1] = &ft_putfifo;
	tab[10] = &ft_putlnk;
	tab[8] = &ft_putreg;
	tab[12] = &ft_putsoc;
	tab[0] = &ft_putwat;
}

int			ft_putblk(void)
{
	ft_putstr("\033[34m");
	return (0);
}

int			ft_putchr(void)
{
	ft_putstr("\033[34m");
	return (0);
}

int			ft_putdir(void)
{
	ft_putstr("\033[33m");
	return (0);
}

int			ft_putfifo(void)
{
	ft_putstr("\033[34m");
	return (0);
}
