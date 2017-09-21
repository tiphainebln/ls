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
	if (file->error)
	{
		ft_putstr(file->name);
		ft_putendl(":");
	}
	if (!op->R || (op->noarg > 2 && file->file == 0))
		write_path(file->path, op->origin, op->noarg, file->relative);
	if (op->l && file->file == 0 && file->error == NULL)
		print_total(file, op);
}

void		directories_as_arg(t_file *file, t_op *op, char *oldpath)
{
	if (ft_strcmp(file->path, oldpath))
	{
		ft_putchar('\n');
		if (file->file == 0)
			write_path(file->path, op->origin, op->noarg, file->relative);
		if (op->l && file->file == 0 && file->error == NULL)
			print_total(file, op);
	}
}

void		multi_arg(t_file *file, t_op *op, char *oldpath)
{
	if (oldpath || op->doubledash)
		ft_putchar('\n');
	if (file->error)
	{
		ft_putstr(file->name);
		ft_putendl(":");
	}
	else
		write_path(file->path, op->origin, op->noarg, file->relative);
	if (op->l && file->file == 0 && file->error == NULL)
		print_total(file, op);
}

t_file		*display_path(t_file *file, t_op *op, char **av, int (*tab[13])())
{
	char	*oldpath;
	int		oldarg;
	int		i;

	oldpath = NULL;
	oldarg = 1;
	i = 0;
	if (errno == ENOENT)
		file->error = op->error;
	while (file)
	{
		if (opt_a(file, op, av) == 0)
		{
			file = empty_directory(file, oldpath, op);
			continue ;
		}
		else if (file->noarg != oldarg && op->noarg > 2 && file->file == 0)
			multi_arg(file, op, oldpath);
		else if (oldpath && file->file == 0)
			directories_as_arg(file, op, oldpath);
		else if (!same_path_everywhere(file, op) && file->file == 0)
			without_recursive(file, op);
		if (oldpath)
			ft_strdel(&oldpath);
		oldpath = ft_strdup(file->path);
		oldarg = file->noarg;
		file = display_standard(file, op, tab);
	}
	return (file);
}
