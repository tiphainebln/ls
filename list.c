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

int 					valuemax(int size, t_op *op, char *name, int origin)
{
	if (name[0] == '.')
	{
		if (op->a)
			return (size);
		else
			return (origin);
	}
	return (size);
}


t_file					*add_file(struct stat *data, t_op *op, char *entry)
{
		t_file			*file;

		file = (t_file *)malloc(sizeof(t_file));
		if (entry[0] == '/')
			file->relative = 0;
		else
			file->relative = 1;
		file->name = get_fname(entry);
		file->type = determine_type(data);
		file = store_basic(file, data);
		file = store_groups_uid(file);
		file->path = get_path(entry, op);
		file->completed = 1;
		file->visited = 1;
		if (op->nbuidspace < ft_strlen(file->uid))
			op->nbuidspace = valuemax(ft_strlen(file->uid), op, file->name, op->nbuidspace);
		if (op->nbgrpspace < ft_strlen(file->grp))
			op->nbgrpspace = valuemax(ft_strlen(file->grp), op, file->name, op->nbgrpspace);
		if (op->nblinkspace < ft_intlen(file->st_nlink))
			op->nblinkspace = valuemax(ft_intlen(file->st_nlink), op, file->name, op->nblinkspace);
		if (op->nbsizespace < ft_intlen(file->st_size))
			op->nbsizespace = valuemax(ft_intlen(file->st_size), op, file->name, op->nbsizespace);
		file->file = 1;
		file->noarg = op->noarg;
		return (file);
}

t_file					*new_file(t_file *file, t_op *op, char *entry)
{
	struct stat 		*data;
	char 				*fullpath;

	if (entry[0] == '/')
		fullpath = ft_strdup(entry);
	else
		fullpath = ft_strjoin(op->origin, entry);
	data = (struct stat *)malloc(sizeof(struct stat));
	if (stat(fullpath, data) == -1)
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
		if (op->nbuidspace < ft_strlen(file->uid))
			op->nbuidspace = valuemax(ft_strlen(file->uid), op, file->name, op->nbuidspace);
		if (op->nbgrpspace < ft_strlen(file->grp))
			op->nbgrpspace = valuemax(ft_strlen(file->grp), op, file->name, op->nbgrpspace);
		if (op->nblinkspace < ft_intlen(file->st_nlink))
			op->nblinkspace = valuemax(ft_intlen(file->st_nlink), op, file->name, op->nblinkspace);
		if (op->nbsizespace < ft_intlen(file->st_size))
			op->nbsizespace = valuemax(ft_intlen(file->st_size), op, file->name, op->nbsizespace);
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

	data = (struct stat *)malloc(sizeof(struct stat));
	if (stat(ft_strjoin(op->current, dirent->d_name), data) == -1)
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
		op->noarg = 1;
		op->relative = 0;
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
