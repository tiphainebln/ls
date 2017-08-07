/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 02:37:40 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/22 02:37:50 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file		*sort_lst(t_file *file, t_op *op)
{
	file = op->begin;
	if (op->r && op->t == 0)
	{
		file = sort(file, REVPATH);
		file = sort(file, REVNAME);
	}
	else if (op->t)
	{
		if (op->r)
		{
			file = sort(file, REVTIME);
			file = sort(file, REVPATHTIME);
		}
		file = sort(file, PATHTIME);
		file = sort(file, TIME);
	}
	else
	{
		file = sort(file, PATH);
		file = sort(file, NAME);
	}
	return (file);
}