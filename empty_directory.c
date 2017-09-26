/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:32:20 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/25 21:52:52 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			only_one(t_file *file, t_op *op)
{
	int		oldarg;

	oldarg = file->noarg;
	file = op->begin;
	while (file)
	{
		if (file->noarg != oldarg)
			return (0);
		file = file->next;
	}
	return (1);
}

int			everything_is_empty(t_file *file)
{
	char	*oldpath;

	oldpath = ft_strdup(file->path);
	while (file && ft_strcmp(file->path, oldpath) == 0)
	{
		if (file->name[0] != '.')
			return (0);
		file = file->next;
	}
	return (1);
}

t_op		*write_and_ddash(t_file *file, t_op *op)
{
	if (op->doubledash == 1)
		ft_putchar('\n');
	if (file->error)
	{
		ft_putstr(file->name);
		ft_putendl(":");
	}
	else
		op->doubledash = write_path(file->path, op->origin, op->noarg,\
				file->relative);
	return (op);
}

t_file		*empty_directory(t_file *file, char *oldpath, t_op *op)
{
	char	*tmp;

	tmp = ft_strstr(file->path, "/.");
	if (op->theresbeenamistake == 0 && ((only_one(file, op) && file->error\
		== 0 && !op->R) || (op->R && tmp && file->sub\
		== 1) || (op->R && only_one(file, op) && op->noarg == 2)))
	{
		if (op->R && tmp && file->sub == 1 && tmp[2] == '/' && everything_is_empty(file) && ft_strcmp(file->name, "."))
		{
			if (ft_strstr(&tmp[2], "/.") == NULL)
			{
				ft_putchar('\n');
				op->doubledash = write_path(file->path, op->origin, op->noarg, \
				file->relative);
			}
		}
		else
		{
			file = file->next;
			return (file);
		}
	}
	else if (oldpath && ft_strcmp(file->name, ".") && \
			only_contains_hidden(file) && ft_strcmp(file->path, oldpath))
	{
		ft_putchar('\n');
		if (file->error)
		{
			ft_putstr(file->name);
			ft_putendl(":");
		}
		else
			op->doubledash = write_path(file->path, op->origin, op->noarg, \
			file->relative);
	}
	else if (ft_strcmp(file->name, ".") && everything_is_empty(file) && !op->r)
		write_and_ddash(file, op);
	file = file->next;
	return (file);
}
