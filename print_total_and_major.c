/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_total_and_major.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 16:36:25 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/11 16:36:28 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file				*print_total(t_file *file, t_op *op)
{
	int				total;

	total = 0;
	while (file != NULL)
	{
		if (file->name[0] == '.')
		{
			if (op->a)
				total += file->st_blocks;
		}
		else
			total += file->st_blocks;
		if (file->next && ft_strcmp(file->path, file->next->path) == 0)
			file = file->next;
		else
			break ;
	}
	if (total >= 0)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	return (file);
}

void				print_major_minor(t_file *file)
{
	ft_putspaces(file, 4);
	ft_putnbr(file->major);
	ft_putstr(",");
	ft_putspaces(file, 5);
	ft_putnbr(file->minor);
	ft_putstr(" ");
}
