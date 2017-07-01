/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 04:17:34 by tbouline          #+#    #+#             */
/*   Updated: 2017/04/04 04:17:35 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file 				*whereDidWeGoWrong(t_op *op, t_file *file, int where)
{
	file = op->begin;
	while (file && file->noarg != where)
		file = file->next;
	return (file);
}

t_file				*isCompleted(t_file *file, t_op *op)
{
	while (file)
	{
		if (file->nameasadir)
		{
			if (ft_strcmp(file->nameasadir, op->current) == 0)
				break ;
		}
		file = file->next;
	}
	file->completed = 1;
	return (file);
}

t_file				*isVisited(t_file *file, t_op *op)
{
	while (file && ft_strcmp(file->path, op->current))
		file = file->next;
	return (file);
}

t_file				*isNothing(t_file *file, t_op *op, t_file *curr_dir)
{
	file->visited = 1;
	file = get_directory(file->nameasadir, file, op, 1);
	file = curr_dir;
	return (file);
}

t_file				*get_sub(t_file *file, t_op *op, int where, t_file *curr_dir)
{
	file = whereDidWeGoWrong(op, file, where);
	curr_dir = file;
	while (file)
	{
		if (file->completed)
		{
			file = file->next;
			if (!file)
			{
				file = curr_dir;
				if (ft_isitover(file))
					return (file);
				file = isCompleted(file, op);
				if (ft_strcmp(curr_dir->path, op->current) == 0)
					return (file);
				change_dir(&op->current, father(op->current), 1);
			}
		}
		else if (file->visited)
			file = isVisited(file, op);
		else
			file = isNothing(file, op, curr_dir);
	}
	return (file);
}
