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

t_file					*print_grp(t_file *file, t_op *op)
{
	ft_putstr(file->grp);
	ft_putspaces(file, op, 2);
	return(file);
}

t_file					*print_uid(t_file *file, t_op *op)
{
	ft_putstr(file->uid);
	ft_putspaces(file, op, 3);
	return (file);
}


t_file					*print_links(t_file *file)
{
	ft_putnbr(file->st_nlink);
	ft_putchar(' ');
	return (file);
}


t_file					*print_size(t_file *file, t_op *op)
{
	ft_putspaces(file, op, 1);
	ft_putnbr(file->st_size);
	ft_putchar(' ');
	return (file);
}


t_file				*print_time(t_file *file)
{
	char			*year;
	char			*date;
	char			*hour;
	char			*strtime;

	strtime = ctime(&file->st_mtimes);
	year = ft_strrchr(strtime, ':') + 4;
	hour = ft_strrchr(strtime, ':') - 5;
	year[4] = '\0';

	hour[5] = '\0';
	date = ft_strchr(strtime, ':') - 9;
	date[6] = '\0';
	ft_putstr(date);
	ft_putchar(' ');
	if (time(NULL) - 15768000 >= file->st_mtimes || time(NULL) < file->st_mtimes)
	{
		ft_putchar(' ');
		ft_putstr(year);
	}
	else
		ft_putstr(hour);
	ft_putchar(' ');
	return (file);
}
