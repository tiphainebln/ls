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

t_file		*highest_order(t_file *file, t_op *op)
{
	char 	*tmp;
	t_file	*tempora;
	char 	*oldpath;

	tmp = NULL;
	oldpath = NULL;
	if (op->R && op->t)
	{
		while (file)
		{
			if (file->sub)
			{
				tempora = file;
				tmp = father(file->path);
				file = op->begin;
				while (ft_strcmp(tmp, file->path))
					file = file->next;
				ft_strdel(&tmp);
				oldpath = ft_strdup(tempora->path);
				if (file->sub == 0)
				{
					file = tempora;
					file->highestsub = 1;
					while (file && ft_strcmp(file->path, oldpath) == 0)
					{
						file->highestsub = 1;
						file = file->next;
					}
				}
				else
				{
					file = tempora;
					file->highestsub = 0;
					while (file && ft_strcmp(file->path, oldpath) == 0)
					{
						file->highestsub = 0;
						file = file->next;
					}
				}
				ft_strdel(&oldpath);
			}
			else
				file = file->next;
		}
	}
	file = op->begin;
	return (file);
}

t_file 		*beyond_space_and_time(t_file *file, t_op *op)
{
	t_file	*tmp;
	int 	i;

	i = 1;
	while (file)
	{
		if (file->highestsub)
		{
			tmp = file;
			tmp->index = i;
			while (file && (ft_strstr(file->path, tmp->path) == NULL || file->highestsub))
				file = file->next;
			while (file && ft_strstr(file->path, tmp->path))
			{
				file->index = i;
				file = file->next;
			}
			while (tmp && tmp->highestsub)
				tmp = tmp->next;
			i++;
			file = tmp;
		}
		else
			file = file->next;
	}
	file = op->begin;
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
	if (op->R && op->t)
	{
		file = highest_order(file, op);
		file = beyond_space_and_time(file, op);
	}
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
