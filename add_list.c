/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 05:47:49 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/24 06:01:13 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file				*add_list(struct stat data, struct dirent *dirent, t_op *op)
{
	t_file			*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = ft_strdup(dirent->d_name);
	file = store_basic(file, data);
	file->path = ft_strdup(op->current);
	file = store_groups_uid(file);
	file = nb_spaces(file, op);
	file->displayname = NULL;
	file = store_lnk(file, op, data);
	file = visited_or_completed(file);
	file->noarg = op->noarg;
	file->relative = op->relative;
	file->file = 0;
	file->error = NULL;
	file->first = 1;
	file->entry = ft_strdup(op->entry);
	file->file_error = 0;
	file->sub = op->sub;
	return (file);
}

t_file				*begin(t_file *file, t_op *op, struct stat data, struct dirent *dirent)
{
	if (op->error)
		file = add_error(dirent->d_name, op);
	else
		file = add_list(data, dirent, op);
	op->begin = file;
	op->latest = file;
	return (file);
}


t_file				*new_list(t_file *file, struct dirent *dirent, t_op *op)
{
	struct stat		data;
	char			*fullname;

	fullname = ft_strjoin(op->current, dirent->d_name);
	if (op->linkname)
		ft_strdel(&op->linkname);
	data = read_links(file, op, fullname, 1);
	if (!file)
		file = begin(file, op, data, dirent);
	else
	{
		file = op->latest;
		if (op->error)
			file->next = add_error(dirent->d_name, op);
		else
			file->next = add_list(data, dirent, op);
		op->latest = file->next;
	}
	free(fullname);
	return (file);
}

t_op				*init(t_op *op, char **env)
{
	int 			i;

	i = -1;
	if (op == NULL)
	{
		op = (t_op *)malloc(sizeof(t_op));
		op = data_op(op);
		while (env[++i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				op->origin = ft_strjoin(&env[i][4], "/");
		}
		op->current = NULL;
		op->error = NULL;
		op->entry = NULL;
		op->order = NULL;
		if (op->origin == NULL)
			manage_error(NULL, ERROR, op, NULL);
	}
	return (op);
}
