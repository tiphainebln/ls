/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:24:51 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:25:00 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file		*print_grp(t_file *file)
{
	ft_putstr(file->grp);
	ft_putspaces(file, 2);
	return (file);
}

t_file		*print_uid(t_file *file)
{
	ft_putstr(file->uid);
	ft_putspaces(file, 3);
	return (file);
}

t_file		*print_links(t_file *file)
{
	ft_putnbr(file->st_nlink);
	ft_putchar(' ');
	return (file);
}

t_file		*print_size(t_file *file)
{
	ft_putspaces(file, 1);
	ft_putnbr(file->st_size);
	ft_putchar(' ');
	return (file);
}
