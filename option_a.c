/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 23:27:24 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/15 15:53:23 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int				ft_cmppostorigin(char *origin, char *path, int free_needed)
{
	int			i;

	i = 0;
	while (origin[i] && path[i] && origin[i] == path[i])
		i++;
	if (path[i])
	{
		if (ft_strstr(&path[i - 1], "/."))
		{
			if (free_needed)
				free(origin);
			return (0);
		}
	}
	if (free_needed)
		free(origin);
	return (1);
}

int				relative_hiddenry(t_file *file, t_op *op, char **argv)
{
	int			i;
	char		*fullpath;

	i = 0;
	while (i != file->noarg - 2)
		i++;
	if (argv[i][0] == '/')
		return (ft_cmppostorigin(argv[i], file->path, 0));
	else
	{
		fullpath = ft_strjoin(op->origin, argv[i]);
		return (ft_cmppostorigin(fullpath, file->path, 1));
	}
}

int				opt_a(t_file *file, t_op *op, char **argv)
{
	if (op->a)
		return (1);
	if (file->name[0] == '.')
		return (0);
	if (ft_strstr(file->path, "/."))
	{
		if (op->noarg == 1 && ft_strstr(op->origin, "/."))
		{
			if (!op->R)
				return (1);
			else
				return (ft_cmppostorigin(op->origin, file->path, 0));
		}
		else if (op->noarg > 1 && ft_strstr(file->path, "/."))
			return (relative_hiddenry(file, op, argv));
		else
			return (0);
	}
	return (1);
}
