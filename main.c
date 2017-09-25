/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:50 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/16 20:23:29 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file		*first_things_first(t_file *file)
{
	t_file	*begin;
	char	*oldpath;

	begin = file;
	oldpath = NULL;
	file->first = 1;
	while (file)
	{
		oldpath = ft_strdup(file->path);
		file = file->next;
		if (file)
		{
			if (ft_strcmp(file->path, oldpath) == 0)
				file->first = 0;
			else
				file->first = 1;
		}
		ft_strdel(&oldpath);
	}
	file = begin;
	return (file);
}

int			main(int argc, char **argv, char **env)
{
	t_op	*op;
	t_file	*file;
	int		i;
	int		(*tab[13])(void);
	char	*oldpath;
	int		oldarg;

	init_tab(tab);
	i = 0;
	op = NULL;
	file = NULL;
	op = init(op, env);
	if (argc > 1)
		epur_and_sort(argv, op, file);
	oldpath = NULL;
	oldarg = 1;
	while (op->order && op->order[i])
	{
		op->error_happened = 0;
		op->noarg++;
		file = get_directory(op->order[i], file, op, 0);
		if (op->R && op->error_happened == 0)
			file = get_sub(file, op, op->noarg, NULL);
		i++;
	}
	file = op->begin;
	if (op->noarg == 1)
	{
		file = get_directory(op->origin, file, op, 0);
		if (op->R)
			file = get_sub(file, op, op->noarg, NULL);
	}
	file = inject_time(file, op);
	file = space_central(file, op);
	if (!file)
		manage_error(file, NOTHINGTODO, op, NULL);
	file = sort_lst(file, op);
	op->begin = file;
	if (op->l && same_path_everywhere(file) && file->file == 0)
		print_total(file, op);
	file = first_things_first(file);
	if (op->d == 0)
		aff_path(file, op, op->order, tab);
	if (oldpath)
		ft_strdel(&oldpath);
	manage_error(file, NOTHINGTODO, op, NULL);
	return (0);
}
