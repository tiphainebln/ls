/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 05:21:39 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/15 15:41:32 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file			*first_node(t_file *file, t_op *op, char *av, struct stat data)
{
	if (op->error)
		file = add_error(av, op);
	else
		file = add_file(data, op, av);
	op->begin = file;
	op->latest = file;
	return (file);
}

t_file			*new_file(t_file *file, t_op *op, char *entry)
{
	struct stat	data;
	char		*fullpath;

	if (op->linkname)
		ft_strdel(&op->linkname);
	if (entry[0] == '/')
		fullpath = ft_strdup(entry);
	else
		fullpath = ft_strjoin(op->origin, entry);
	data = read_links(file, op, fullpath, 1);
	if (!file)
		file = first_node(file, op, entry, data);
	else
	{
		file = op->latest;
		if (op->error)
			file->next = add_error(entry, op);
		else
			file->next = add_file(data, op, entry);
		op->latest = file->next;
	}
	free(fullpath);
	return (file);
}

t_file			*add_more(t_file *file, t_op *op, char *entry)
{
	file->completed = 1;
	file->visited = 1;
	file->file = 1;
	file->error = NULL;
	file->noarg = op->noarg;
	file->first = 1;
	file->nameasadir = NULL;
	file->entry = ft_strdup(entry);
	file->file_error = 0;
	file->sub = op->sub;
	file->errorname = NULL;
	file->directorytime = 0;
	file->link = op->link;
	file->index = 0;
	return (file);
}

t_file			*add_file(struct stat data, t_op *op, char *entry)
{
	t_file		*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (entry[0] == '/')
		file->relative = 0;
	else
		file->relative = 1;
	file = store_lnk(file, op, data);
	file->name = get_fname(entry);
	file->displayname = ft_strdup(entry);
	file = store_basic(file, data);
	file = store_groups_uid(file);
	file->path = store_path(entry, op);
	file = add_more(file, op, entry);
	return (file);
}
