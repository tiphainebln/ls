/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:51:42 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/10 15:51:44 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file			*store_lnk(t_file *file, t_op *op, struct stat data)
{
	if (op->link)
	{
		file->type = 10;
		file->typereal = determine_type(data);
		file->linkname = ft_strdup(op->linkname);
	}
	else
	{
		file->type = determine_type(data);
		file->linkname = NULL;
	}
	return (file);
}

struct stat		read_links(t_file *file, t_op *op, char *fullpath, int verbose)
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
		if (lstat(fullpath, &data) == -1 && verbose == 1)
		{
			manage_error(file, ARGUMENT, op, NULL);
			op->error = ft_strdup(strerror(errno));
		}
		op->link = 1;
		op->linkname = ft_strdup(buf);
	}
	if (len <= 0 && stat(fullpath, &data) == -1 && verbose == 1)
	{
		manage_error(file, ARGUMENT, op, NULL);
		op->error = ft_strdup(strerror(errno));
	}
	return (data);
}
