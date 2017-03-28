/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:12:19 by tbouline          #+#    #+#             */
/*   Updated: 2017/03/27 03:27:53 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file			*display_a(t_file *file, t_op *op)
{
	while (file)
	{
		if (opt_a(file, op) == 0)
		{
			file = file->next;
			continue ;
		}
		ft_putstr(file->name);
		ft_putchar('\n');
	}
	file = file->next;
	return (file);
}

int 			opt_a(t_file *file, t_op *op)
{
	if (file->name[0] == '.')
	{
		if (!op->a)
			return (0);
	}
	return (1);
}

t_file			*long_format(t_file *file, t_op *op)
{
	//if (file->type == DT_DIR)
		//ft_putstr("\033[31m");
	//else
	//	ft_putstr("\033[32m");
	file_type_letter(file);
	print_rights(file, op);
	print_links(file, op);
	print_uid(file, op);
	print_grp(file, op);
	print_size(file, op);
	print_time(file);
	ft_putstr(file->name);
	ft_putchar('\n');
	ft_putstr("\033[00m");
	return (file);
}

void			ft_putspaces(t_file *file, t_op *op, int choice)
{
	int space;

	space = 0;
	if (choice == 1)
		space = op->nbsizespace - ft_intlen(file->st_size);
	else if (choice == 2)
		space = op->nbgrpspace - ft_strlen(file->grp);
	else if (choice == 3)
		space = op->nbuidspace - ft_strlen(file->uid);
	else
		space = op->nblinkspace - ft_intlen(file->st_nlink);
	if (choice != 2)
		ft_putstr("  ");
	while (--space >= 0)
		ft_putchar(' ');
}
