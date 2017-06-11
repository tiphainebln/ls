/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 04:08:32 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/03 04:08:47 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		without_recursive(t_file *file, t_op *op)
{
	if (!op->R || (op->noarg > 2 && file->file == 0))
		write_path(file->path, op->origin, op->noarg, file->relative);
	if (op->l && file->file == 0)
		print_total(file, op);
}

void		directories_as_arg(t_file *file, t_op *op, char *oldpath)
{
	if (ft_strcmp(file->path, oldpath))
	{
		ft_putchar('\n');
		if (file->file == 0)
			write_path(file->path, op->origin, op->noarg, file->relative);
		if (op->l && file->file == 0)
			print_total(file, op);
	}
}

void		multi_arg(t_file *file, t_op *op, char *oldpath)
{
	if (oldpath)
		ft_putchar('\n');
	write_path(file->path, op->origin, op->noarg, file->relative);
	if (op->l)
		print_total(file, op);
}

t_file			*empty_directory(t_file *file, char *oldpath, t_op *op)
{
	if (oldpath && ft_strcmp(file->name, ".") && only_contains_hidden(file) && ft_strcmp(file->path, oldpath))
	{
		ft_putchar('\n');
		write_path(file->path, op->origin, op->noarg, file->relative);
	}
	file = file->next;
	return (file);
}

t_file			*display_path(t_file *file, t_op *op, char **argv, int (*tab[13])(void))
{
	char	*oldpath;
	int 	oldarg;

	oldpath = NULL;
	oldarg = 1;
	while (file)
	{
		if (opt_a(file, op, argv) == 0)
		{
			file = empty_directory(file, oldpath, op);
			continue ;
		}
		else if (file->noarg != oldarg && op->noarg > 2 && file->file == 0)
			multi_arg(file, op, oldpath);
		else if (oldpath)
			directories_as_arg(file, op, oldpath);
		else if (!same_path_everywhere(file))
			without_recursive(file, op);
		if (oldpath)
			ft_strdel(&oldpath);
		oldpath = ft_strdup(file->path);
		oldarg = file->noarg;
		if (file->error)
		 	ft_putendl(file->error);
		else if (op->l)
			long_format(file, op, tab);
		else
			(file->file) ? ft_putendl(file->displayname) : ft_putendl(file->name);
		//tab[file->type]();
		// ft_putstr("\033[00m");
		file = file->next;
	}
	return (file);
}