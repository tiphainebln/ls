/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 23:27:52 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/01 23:28:16 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

struct stat		read_links(t_file *file, t_op *op, char *fullpath)
{
	int			len;
	char		buf[1024];
	struct stat data;

	len = 0;
	op->link = 0;
	if (op->linkname)
		ft_strdel(&op->linkname);
	if ((len = readlink(fullpath, buf, 1024)) > 0)
	{
		buf[len] = '\0';
		if (lstat(fullpath, &data) == -1)
		{
			manage_error(file, ARGUMENT, op, NULL);
			op->error = ft_strdup(strerror(errno));
		}
		op->link = 1;
		op->linkname = ft_strdup(buf);
	}
	if (len <= 0 && errno != ELOOP && stat(fullpath, &data) == -1)
	{
		manage_error(file, ARGUMENT, op, NULL);
		op->error = ft_strdup(strerror(errno));
	}
	return (data);
}

t_op 		*data_op(t_op *op)
{
	op->a = 0;
	op->r = 0;
	op->R = 0;
	op->l = 0;
	op->t = 0;
	op->begin = NULL;
	op->origin = NULL;
	op->nbsizespace = 0;
	op->nblinkspace = 0;
	op->nbgrpspace = 0;
	op->nbuidspace = 0;
	op->nbminorspace = 0;
	op->nbmajorspace = 0;
	op->noarg = 1;
	op->relative = 0;
	op->linkname = NULL;
	op->link = 0;
	op->latest = NULL;
	return (op);
}

t_file		*visited_or_completed(t_file *file)
{
	if (file->type == DT_DIR && ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
	{
		file->visited = 0;
		file->completed = 0;
		file->nameasadir = ft_str3join(file->path, file->name, "/");
	}
	else
	{
		file->completed = 1;
		file->visited = 1;
		file->nameasadir = NULL;
	}
	return (file);
}