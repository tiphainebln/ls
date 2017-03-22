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

t_file					*print_grp(t_file *file)
{
	struct group 	*grp;
	char			*gid;

	grp = (struct group *)malloc(sizeof(struct group));
	grp = getgrgid(file->st_gid);
	if (((grp = getgrgid(file->st_gid)) == NULL))
	{
		gid = ft_itoa(file->st_gid);
		ft_putstr(gid);
		ft_putstr("  ");
	}
	else
	{
		gid = ft_strdup(grp->gr_name);
		ft_putstr(grp->gr_name);
		ft_putstr("  ");
	}
	grp = NULL;
	free(grp);
	return(file);
}

t_file					*print_uid(t_file *file)
{
	struct passwd	*uid;
	char			*id;

	uid = (struct passwd *)malloc(sizeof(struct passwd));
	uid = getpwuid(file->st_uid);
	if (((uid = getpwuid(file->st_uid)) == NULL))
	{	
		id = ft_itoa(file->st_uid);
		ft_putstr(id);
		ft_putstr("  ");
	}
	else
	{ 
		id = ft_strdup(uid->pw_name);
		ft_putstr(uid->pw_name);
		ft_putstr("  ");
	}
	uid = NULL;
	free(uid);
	return (file);
}


t_file					*print_links(t_file *file, t_op *op)
{
	if (file->st_nlink >= 0)
	{
		ft_putnbr(file->st_nlink);
		ft_putchar(' ');
	}
	return (file);
}


t_file					*print_size(t_file *file, t_op *op)
{
	if (file->st_size >= 0)
	{
		ft_putnbr(file->st_size);
		ft_putchar(' ');
	}
	return (file);
}

/*
t_file				*print_time(t_file *file, t_op *op)
{
	time_t			actualtime;

	ctime(&actualtime);
	while (file)
	{
		ft_putstr(&actualtime);
		file = file->next;
	}
	return (file);
}
*/