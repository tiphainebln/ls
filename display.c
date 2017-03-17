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

t_file			*opt_a(t_file *file, t_op *op)
{
	while (file)
	{
		if (op->a == 1 && ft_strcmp(file->name, "..") == 0 &&\
			ft_strcmp(file->name, ".") == 0 && ft_strcmp(&file->name[0], ".") == 0)
		{
			ft_putstr(file->name);
			ft_putchar('\n');
			file->next = file;
		}
	}
	return (file);
}

t_file			*long_format(t_file *file, t_op *op)
{
	file = op->begin;
	print_total(file, op);
	while (file)
	{
		if (op->l == 1 && ft_strcmp(file->name, "..") != 0 &&\
			ft_strcmp(file->name, ".") != 0)
		{
			file_type_letter(file);
			print_rights(file);
			print_links(file, op);
			print_uid(file);
			print_grp (file);
			print_size(file, op);
			ft_putstr(file->name);
			ft_putchar('\n');
			ft_putchar('\n');
		}
		file = file->next;
	}
	return (file);
}

// corriger print_links -> lolo devrait en avoir deux
// corriger print_size -> tout est mis a 0 hors lolo, ok et testdir2 ne sont pas = 0
// le -l est affiché, il ne devrait pas (voir else de directories)
// tester, est ce que cela fontionne sans passer un dir en argv ? les informations sont elles correctement recuperees ? 
// ajouter time