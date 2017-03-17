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

t_file	*sort(t_file *t_file)
{
	while (is_sorted(begin) == 0)
	{
		list = begin;
		while (list->next)
		{
			if (cmp_links(list, list->next) == 0)
				swap_list(&list, &list->next);
			list = list->next;
		}
	}
	return (t_file);
}

void	swap_list(t_file **a, t_file **b)
{
	t_file	*c;

	c = *a;
	*a = *b;
	*b = c;
}

int		cmp_links(t_file *a, t_file *b)
{
	if (a->time > b->time)
		return (0);
	return (1);
}

int		is_sorted(t_file *begin)
{
	while (begin->next)
	{
		if (cmp_links(begin, begin->next) == 0)
			return (0);
		begin = begin->next;
	}
	return (1);
}