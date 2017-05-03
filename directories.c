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

t_file				*get_directory(char *entry, t_file *file, t_op *op, int sub)
{
	DIR 			*fd;

	op->relative = 0;
	if (((fd = opendir(entry))) != NULL)
	{
		if (entry[0] == '/' || sub)
		{
			if (entry[ft_strlen(entry) - 1] == '/')
				change_dir(&op->current, entry);
			else
				change_dir(&op->current, ft_strjoin(entry, "/"));
		}
		else
		{
			op->relative = 1;
			change_dir(&op->current, ft_strjoin(ft_strjoin(op->origin, entry), "/"));
		}
		file = read_content(file, fd, op);
		closedir(fd);
	}
	else
	{
		if (errno == ENOTDIR)
			file = new_file(file, op, entry);
		else
			error(file, PERMISSION, op, entry);
	}
	return (file);
}

t_file				*read_content(t_file *file, DIR *fd, t_op *op)
{
	struct dirent	*dirent;

	if (!(dirent = (struct dirent *)malloc(sizeof(struct dirent))))
		error(file, MALLOC_ERROR, op, NULL);
	while (((dirent = readdir(fd)) != NULL))
	{
		file = op->begin;
		file = new_list(file, dirent, op);
		if (op->relative)
			file->relative = 1;
	}
	return (file);
}
