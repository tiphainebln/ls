/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:34 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/23 03:52:39 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ls.h"

void		free_file(t_file *file, t_file *tmp)
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
		tmp = file;
		file = file->next;
		free(tmp);
	}
}

void 		ft_free(t_file *file, t_op *op, int error)
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

t_file					*add_error(char *name, t_op *op)
{
	t_file			*file;

	file = (t_file *)malloc(sizeof(t_file));
	// if (ft_strstr(name, "../"))
	// 	file->name = ft_strdup(ft_strstr(name, "../"));
	// else
	file->name = ft_strdup(name);
	file->path = store_path(name, op);
	file->st_size = 0;
	file->type = 0;
	file->st_nlink = 0;
	file->st_mode = 0;
	file->st_gid = 0;
	file->st_uid = 0;
	file->st_blocks = 0;
	file->st_blksize = 0;
	file->st_mtimes = 0;
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
	file->error = ft_str3join(file->name, ": ", op->error);
	if (op->error)
		ft_strdel(&op->error);
	file->first = 1;
	file->next = NULL;
	file->file_error = 1;
	return (file);
}

void		manage_error(t_file *file, int error, t_op *op, char *entry)
{
	if (error == USAGE)
		ft_putendl_fd("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]", 2);
	else if (error != NOTHINGTODO && errno != ELOOP && error != PERMISSION)
		perror(entry);
	if (error == OPTION || error == MALLOC_ERROR || error == NOTHINGTODO)
	{
		file = op->begin;
		ft_free(file, op, error);
	}
}


/*
a tester :
ls /etc ; ls -l /etc
ls -l /dev;
ls 9 8 7 5 4 4 4 5 662123 4 6 2;
ls 9 5 4 8 7 1 3 + plusieurs fichier
ls plusieurs fichiers 8 4 2 34 6 4
mkdir testdir; chmod 000 testdir; ls -l testdir
ls -lat -> ou se trouve "." et ".." ? Pourquoi?
ls -lratR -> comprenez vous la raison de l'ordre de chaque lignes?
- permission denied - essaye de lire un fichier sans avoir les droits d'acces
- No such file or directory - si le dossier/fichier n'existe pas
- cd /dev etre sur que le ls peut s'effectuer correctement dans n'importe quelle circonstances (majeurs/mineurs des devices dans /dev)

ls: illegal option -- z
usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]
			ft_putstr("ls: illegal option -- ");
			ft_putchar(argv[i]);
			ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
*/
