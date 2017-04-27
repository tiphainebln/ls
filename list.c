/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:22:07 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:22:10 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file					*add_file(struct stat *data, t_op *op, char *entry)
{
		t_file			*file;

		file = (t_file *)malloc(sizeof(t_file));
		if (entry[0] == '/')
			file->relative = 0;
		else
			file->relative = 1;
		if (op->link)
			file->linkname = ft_strdup(op->linkname);
		else
			file->linkname = NULL;
		file->name = get_fname(entry);
		file->displayname = ft_strdup(entry);
		file->type = determine_type(data);
		file = store_basic(file, data);
		file = store_groups_uid(file);
		file->path = get_path(entry, op);
		file->completed = 1;
		file->visited = 1;
		file = nb_spaces(file, op);
		file->file = 1;
		file->noarg = op->noarg;
		return (file);
}

t_file					*new_file(t_file *file, t_op *op, char *entry)
{
	struct stat 		*data;
	char 				*fullpath;
	char 				buf[1024];
	int 				len;

	data = (struct stat *)malloc(sizeof(struct stat));
	op->link = 0;
	if (entry[0] == '/')
		fullpath = ft_strdup(entry);
	else
		fullpath = ft_strjoin(op->origin, entry);
	if (op->linkname)
		ft_strdel(&op->linkname);
	else if ((len = readlink(fullpath, buf, 1024)) > 0)
	{
		buf[len] = '\0';
		if (lstat(fullpath, data) == -1)
		{
			error(ARGUMENT);
			return (file);
		}
		op->link = 1;
		op->linkname = ft_strdup(buf);
	}
	else if (stat(fullpath, data) == -1)
	{
		error(ARGUMENT);
		return (file);
	}
	if (!file)
	{
		file = add_file(data, op, entry);
		op->begin = file;
	}
	else
	{
		while (file->next)
			file = file->next;
		file->next = add_file(data, op, entry);
	}
	return (file);
}

t_file					*add_list(struct stat *data, struct dirent *dirent, t_op *op)
{
		t_file			*file;

		file = (t_file *)malloc(sizeof(t_file));
		file->name = ft_strdup(dirent->d_name);
		file->type = dirent->d_type;
		file = store_basic(file, data);
		file->path = ft_strdup(op->current);
		file = store_groups_uid(file);
		file = nb_spaces(file, op);
		file->displayname = NULL;
		if (op->link)
			file->linkname = ft_strdup(op->linkname);
		else
			file->linkname = NULL;
		if (file->type == DT_DIR && ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
		{
			file->visited = 0;
			file->completed = 0;
		}
		else
		{
			file->completed = 1;
			file->visited = 1;
		}
		file->noarg = op->noarg;
		file->relative = 0;
		file->file = 0;
		return (file);
}

t_file					*new_list(t_file *file, struct dirent *dirent, t_op *op)
{
	struct stat 		*data;
	char				buf[1024];
	int 				len;

	data = (struct stat *)malloc(sizeof(struct stat));
	op->link = 0;
	if (op->linkname)
		ft_strdel(&op->linkname);
	if ((len = readlink(ft_strjoin(op->current, dirent->d_name), buf, 1024)) > 0)
	{
		buf[len] = '\0';
		if (lstat(ft_strjoin(op->current, dirent->d_name), data) == -1)
		{
			error(ARGUMENT);
			return (file);
		}
		op->link = 1;
		op->linkname = ft_strdup(buf);
	}
	else if (stat(ft_strjoin(op->current, dirent->d_name), data) == -1)
	{
		error(ARGUMENT);
		return (file);
	}
	if (!file)
	{
		file = add_list(data, dirent, op);
		op->begin = file;
	}
	else
	{
		while (file->next)
			file = file->next;
		file->next = add_list(data, dirent, op);
	}
	return (file);
}

t_op	*init(t_op *op, char **env)
{
	int 		i;

	i = -1;
	if (op == NULL)
	{
		op = (t_op *)malloc(sizeof(t_op));
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
		while (env[++i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				op->origin = ft_strjoin(ft_strsub(env[i], 4, ft_strlen(env[i]) - 4), "/");
		}
		op->current = NULL;
		if (op->origin == NULL)
			error(ERROR);
	}
	return (op);
}
