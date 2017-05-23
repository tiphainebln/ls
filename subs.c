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

void				change_dir(char **old, char *new, int free_needed)
{
	if (*old)
		free(*old);
	*old = ft_strdup(new);
	if (free_needed)
		free(new);
}

int					ft_second_to_last(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (--i > 0)
	{
		if (str[i] == '/')
			return (i);
	}
	return (0);
}

int					ft_isitover(t_file *file)
{
	while (file)
	{
		if (file->completed == 0)
			return (0);
		file = file->next;
	}
	return (1);
}

char 				*father(char *current)
{
	char 			*father;
	char 			*mother;

	father = ft_strsub(current, 0, ft_second_to_last(current));
	mother = ft_strjoin(father, "/");
	free(father);
	return (mother);
}

t_file				*get_sub(t_file *file, t_op *op, int where)
{
	t_file	*curr_dir;

	file = op->begin;
	while (file && file->noarg != where)
		file = file->next;
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
				if (ft_strcmp(curr_dir->path, op->current))
					change_dir(&op->current, father(op->current), 1);
				else
					return (file);
			}
		}
		else if (file->visited)
		{
			while (file && ft_strcmp(file->path, op->current))
				file = file->next;
		}
		else
		{
			file->visited = 1;
			file = get_directory(file->nameasadir, file, op, 1);
			file = curr_dir;
		}
	}
	return (file);
}
