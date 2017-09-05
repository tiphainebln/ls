/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 16:27:04 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/11 16:27:09 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

time_t 	get_time(char *path, char *name, t_op *op)
{
	char 			*fullpath;
	struct stat 	this;

	fullpath = NULL;
	fullpath = ft_strjoin(path, name);
	this = read_links(NULL, op, fullpath, 0);
	ft_strdel(&fullpath);
	return (this.st_mtimespec.tv_sec);
}

t_file		*inject_time(t_file *file, t_op *op)
{
	time_t 	time;
	time_t 	oldtime;
	char 	*oldpath;

	time = 0;
	oldpath = NULL;
	file = op->begin;
	while (file)
	{
		oldtime = time;
		if (oldpath)
		{
			if (ft_strcmp(file->path, oldpath))
				time = get_time(file->path, file->name, op);
		}
		else
			time = get_time(file->path, file->name, op);
		if (oldtime != time || !oldpath)
			oldpath = ft_strdup(file->path);
		file->foldertime = time;
		file = file->next;
	}
	file = op->begin;
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
		if (year[0] == ' ')
			ft_putstr("10000");
		else
			ft_putstr(year);
	}
	else
		ft_putstr(hour);
	ft_putchar(' ');
	return (file);
}