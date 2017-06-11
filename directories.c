/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 00:17:32 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/28 00:17:34 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void				relative_or_absolute(t_op *op, int sub, char *entry)
{
	if (entry[0] == '/' || sub)
	{
		if (entry[ft_strlen(entry) - 1] == '/')
			change_dir(&op->current, entry, 0);
		else
			change_dir(&op->current, ft_strjoin(entry, "/"), 1);
		if (sub)
			op->relative = 1;
	}
	else
	{
		op->relative = 1;
		change_dir(&op->current, ft_str3join(op->origin, entry, "/"), 1);
	}
}

t_file				*get_directory(char *entry, t_file *file, t_op *op, int sub)
{
	DIR 			*fd;

	op->relative = 0;
	op->entry = ft_strdup(entry);
	if (((fd = opendir(entry))) != NULL)
	{
		relative_or_absolute(op, sub, entry);
		file = read_content(file, fd, op);
		closedir(fd);
	}
	else
	{
		if (errno == ENOTDIR)
			file = new_file(file, op, entry);
		else
		{
			if (sub)
				file->completed = 1;
			manage_error(file, PERMISSION, op, entry);
			op->error = ft_strdup(strerror(errno));
			if (!file)
			{
				file = add_error(entry, op);
				op->begin = file;
				op->latest = file;
			}
			else
			{
				file = op->latest;
				file->next = add_error(entry, op);
				op->latest = file->next;
			}
		}
	}
	if (op->entry)
		ft_strdel(&op->entry);
	return (file);
}

t_file				*read_content(t_file *file, DIR *fd, t_op *op)
{
	struct dirent	*dirent;

	while (((dirent = readdir(fd)) != NULL))
	{
		file = op->begin;
		file = new_list(file, dirent, op);
	}
	return (file);
}
