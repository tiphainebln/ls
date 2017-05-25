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

t_file					*add_file(struct stat data, t_op *op, char *entry)
{
		t_file			*file;

		file = (t_file *)malloc(sizeof(t_file));
		if (entry[0] == '/')
			file->relative = 0;
		else
			file->relative = 1;
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
		file->name = get_fname(entry);
		file->displayname = ft_strdup(entry);
		file = store_basic(file, data);
		file = store_groups_uid(file);
		file->path = get_path(entry, op);
		file->completed = 1;
		file->visited = 1;
		file = nb_spaces(file, op);
		file->file = 1;
		file->error = 0;
		file->noarg = op->noarg;
		file->first = 1;
		file->nameasadir = NULL;
		return (file);
}

t_file					*new_file(t_file *file, t_op *op, char *entry)
{
	struct stat 		data;
	char 				*fullpath;
	char 				buf[1024];
	int 				len;

	op->link = 0;
	op->error = 0;
	if (entry[0] == '/')
		fullpath = ft_strdup(entry);
	else
		fullpath = ft_strjoin(op->origin, entry);
	if (op->linkname)
		ft_strdel(&op->linkname);
	if ((len = readlink(fullpath, buf, 1024)) > 0)
	{
		buf[len] = '\0';
		if (lstat(fullpath, &data) == -1)
		{
			error(file, ARGUMENT, op, entry);
			return (file);
		}
		op->link = 1;
		op->linkname = ft_strdup(buf);
	}
	if (len <= 0 && stat(fullpath, &data) == -1)
		error(file, ARGUMENT, op, entry);
	else if (!file)
	{
		file = add_file(data, op, entry);
		op->begin = file;
		op->latest = file;
	}
	else
	{
		file = op->latest;
		file->next = add_file(data, op, entry);
		op->latest = file->next;
	}
	free(fullpath);
	return (file);
}

t_file					*add_list(struct stat data, struct dirent *dirent, t_op *op)
{
		t_file			*file;

		file = (t_file *)malloc(sizeof(t_file));
		file->name = ft_strdup(dirent->d_name);
		file = store_basic(file, data);
		file->path = ft_strdup(op->current);
		file = store_groups_uid(file);
		file = nb_spaces(file, op);
		file->displayname = NULL;
		if (op->link)
		{
			file->linkname = ft_strdup(op->linkname);
			file->type = 10;
			file->typereal = dirent->d_type;
		}
		else
		{
			file->type = dirent->d_type;
			file->linkname = NULL;
		}
		if (file->type == DT_DIR && ft_strcmp(file->name, ".") && ft_strcmp(file->name, "..")) // && got_rights(file, op))
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
		file->noarg = op->noarg;
		file->relative = 0;
		file->file = 0;
		file->error = 0;
		file->first = 1;
		return (file);
}

// 7255 7008

// ==39251==    still reachable: 11,801 bytes in 57 blocks
// ==39251==         suppressed: 22,238 bytes in 190 blocks

t_file					*new_list(t_file *file, struct dirent *dirent, t_op *op)
{
	struct stat 		data;
	char				buf[1024];
	int 				len;
	char 				*fullname;

	op->link = 0;
	op->error = 0;
	len = 0;
	fullname = ft_strjoin(op->current, dirent->d_name);
	if (op->linkname)
		ft_strdel(&op->linkname);
	if (dirent->d_type == 10 && (len = readlink(fullname, buf, 1024)) > 0)
	{
		buf[len] = '\0';
		if (lstat(fullname, &data) == -1)
		{
			error(file, ARGUMENT, op, dirent->d_name);
			return (file);
		}
		op->link = 1;
		op->linkname = ft_strdup(buf);
	}
	if (len <= 0 && stat(fullname, &data) == -1)
		error(file, ARGUMENT, op, dirent->d_name);
	else if (!file)
	{
		file = add_list(data, dirent, op);
		op->begin = file;
		op->latest = file;
	}
	else
	{
		file = op->latest;
		file->next = add_list(data, dirent, op);
		op->latest = file->next;
	}
	free(fullname);
	return (file);
}

/* OPTIS: STR3JOIN => lire de la doc sur le "paradoxe" du line painter, readlink prend apparemment du temps donc on le fait que si applicable, op->latest evite une boucle de plus en plus longue à chaque appel*/

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
		op->latest = NULL;
		while (env[++i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				op->origin = ft_strjoin(&env[i][4], "/");
		}
		op->current = NULL;
		if (op->origin == NULL)
			error(NULL, ERROR, op, NULL);
	}
	return (op);
}
