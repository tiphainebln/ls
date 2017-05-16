/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:13:25 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:13:27 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

// int			cmp_time(t_file *a, t_file *b)
// {
// 	if (a->st_mtimes < b->st_mtimes)
// 	{
// 		ft_putendl("aaa");
// 		return (a->st_mtimes < b->st_mtimes);
// 	}
// 	else if (a->st_mtimes == b->st_mtimes)
// 	{
// 		if (a->st_mtimes < b->st_mtimes)
// 		{
// 			ft_putendl("bbb");
// 			return (a->st_mtimes < b->st_mtimes);
// 		}
// 		else if (a->st_mtimes == b->st_mtimes)
// 		{
// 			ft_putendl("ccc");
// 			return (ft_strcmp(a->name, b->name));
// 		}
// 	}
// 	return (0);
// }

t_file		*swap_list(t_file *a, t_file *b)
{
	a->next = b->next;
	b->next = a;
	return (b);
}

int			cmp_links(t_file *a, t_file *b, int tri)
{
	if (tri == PATH)
	{
		if (ft_strcmp(a->path, b->path) > 0)
			return (0);
		return (1);
	}
	if (tri == NAME)
	{
		if (ft_strcmp(a->name, b->name) > 0 && ft_strcmp(a->path, b->path) == 0)
			return (0);
		return (1);
	}
	if (tri == REVERSE)
	{
		if (ft_strcmp(ft_strjoin(a->path, a->name), ft_strjoin(b->path, b->name)) < 0)
			return (0);
		return (1);
	 }
	 // if (tri == TIME)
		// cmp_time(a, b);
	 //return (0);
	 else
	 	return (1);
}

// t_file		*get_end_of_path(t_file *file)
// {
// 	while (ft_strcmp(file->path, file->path->next) = 0)
// 		file = file->next;
	
// }

t_file		*sort(t_file *file, int tri)
{
	t_file	*start;
	t_file	*a;
	t_file	*b;
	int		changed;
	// t_file	*end;

	// if UN SEUL ARGUMENT ET !R
	// if (file->noarg == 1 && !R)
	// 	end = NULL;
	// else
	// 	end = get_end_of_path(file);
	changed = 1;
	start = (t_file *)malloc(sizeof(t_file));
	start->next = file;
	while (changed)
	{
		changed = 0;
		a = start;
		b = start->next;
		while (b->next)
		{
			if (cmp_links(b, b->next, tri) == 0)
			{
				a->next = swap_list(b, b->next);
				changed = 1;
			}
			a = b;
			if (b->next)
				b = b->next;
		}
	}
	b = start->next;
	free(start);
	return (b);
}