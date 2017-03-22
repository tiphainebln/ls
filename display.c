/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:12:19 by tbouline          #+#    #+#             */
/*   Updated: 2017/03/10 04:12:24 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

// USAGE IN YOUR FINAL PRINT LOOP
//	if (opt_a(file, op) == 0)
//	{
//		file = file->next;
//		continue ;
//	}
//	print dsifgjidfgj
//	print dfgiogjfddfg
//  print \n
//	file = file->next;

//	___
//	|8|
//	|8|
//	|8|
//	|8|
//	 V

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
		{
			return (0);
		}	
	}
	return (1);
}

t_file			*long_format(t_file *file, t_op *op)
{
	file = op->begin;
	print_total(file, op);
	while (file)
	{
		if (op->l == 1 && file->name[0] != '.')
		{
			ft_putstr("\033[34m");
			file_type_letter(file);
			print_rights(file, op);
			print_links(file, op);
			print_grp(file, op);
			print_uid(file);
			print_size(file, op);
			ft_putstr(file->name);
			ft_putchar('\n');
			file = file->next;
			ft_putstr("\033[00m");
		}
	}
	return (file);
}

void			ft_putspaces(t_file *file, t_op *op, int choice)
{
	int space;

	space = 0;
	if (choice == 1)
		space = op->nbsizespace - ft_intlen(file->st_size);
	else
		space = op->nblinkspace - ft_intlen(file->st_nlink);
	while (--space >= 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

// corriger print_links -> lolo devrait en avoir deux
// corriger print_size -> tout est mis a 0 hors lolo, ok et testdir2 ne sont pas = 0
// le -l est affiché, il ne devrait pas (voir else de directories)
// tester, est ce que cela fontionne sans passer un dir en argv ? les informations sont elles correctement recuperees ? 
// ajouter time