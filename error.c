/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:34 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/15 15:50:37 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			free_file(t_file *file, t_file *tmp)
{
	while (file)
	{
		if (file->nameasadir)
			free(file->nameasadir);
		if (file->name)
			free(file->name);
		if (file->uid)
			free(file->uid);
		if (file->grp)
			free(file->grp);
		if (file->displayname)
			free(file->displayname);
		if (file->linkname)
			free(file->linkname);
		if (file->errorname)
			free(file->errorname);
		tmp = file;
		file = file->next;
		free(tmp);
	}
}

void			ft_free(t_file *file, t_op *op, int error)
{
	t_file	*tmp;

	tmp = NULL;
	if (file)
		free_file(file, tmp);
	if (op)
	{
		if (op->origin)
			free(op->origin);
		if (op->current)
			free(op->current);
		if (op->linkname)
			free(op->linkname);
		free(op);
	}
	exit((error) ? 1 : 0);
}

t_file			*more_errors(t_file *file, char *name, t_op *op)
{
	file->displayname = NULL;
	file->nameasadir = NULL;
	file->uid = NULL;
	file->grp = NULL;
	file->linkname = NULL;
	file->noarg = op->noarg;
	file->visited = 1;
	file->completed = 1;
	file->entry = ft_strdup(name);
	file->relative = op->relative;
	file->file = 0;
	file->sub = op->sub;
	file->errorname = get_fname(name);
	file->error = str3join(file->errorname, ": ", op->error);
	if (op->error)
		ft_strdel(&op->error);
	file->first = 1;
	file->next = NULL;
	file->file_error = 1;
	file->directorytime = 0;
	file->acl = 0;
	file->attr = 0;
	file->rightsize = 0;
	return (file);
}

t_file			*add_error(char *name, t_op *op)
{
	t_file		*file;
	char		*tmp;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	tmp = store_path(name, op);
	if (tmp[ft_strlen(tmp) - 1] != '/')
		file->path = ft_strjoin(tmp, "/");
	else
		file->path = ft_strdup(tmp);
	ft_strdel(&tmp);
	file->st_size = 0;
	file->type = 0;
	file->st_nlink = 0;
	file->st_mode = 0;
	file->st_gid = 0;
	file->st_uid = 0;
	file->st_blocks = 0;
	file->st_blksize = 0;
	file->st_mtimes = 0;
	file = more_errors(file, name, op);
	return (file);
}

void			manage_error(t_file *f, int error, t_op *op, char *av)
{
	op->theresbeenamistake = 1;
	if (error != NOTHINGTODO && errno != ELOOP && error != OPTION)
	{
		ft_putstr_fd("ls: ", 2);
		perror(av);
	}
	if (error == OPTION || error == NOTHINGTODO)
	{
		if (error == OPTION)
		{
			ft_putstr_fd("ls: illegal option --", 2);
			ft_putchar_fd(av[0], 2);
			ft_putchar_fd('\n', 2);
			ft_putendl_fd("usage: ls [-Rraltd1G] [file ...]", 2);
		}
		f = op->begin;
		ft_free(f, op, error);
	}
}
