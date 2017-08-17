/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:19:57 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/13 15:19:59 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file			*display_standard(t_file *file, t_op *op, int (*tab[13])(void))
{
	if (file->error)
		ft_putendl_fd(file->error, 2);
	else if (op->l)
		long_format(file, op, tab);
	else
		(file->file) ? ft_putendl(file->displayname) : ft_putendl(file->name);
	/*
	**tab[file->type]();
	**ft_putstr("\033[00m");
	*/
	file = file->next;
	return (file);
}

t_file			*long_format(t_file *file, t_op *op, int (*tab[13])(void))
{
	file_type_letter(file);
	print_rights(file, op);
	print_links(file);
	print_uid(file, op);
	print_grp(file, op);
	if (file->minor == -1)
		print_size(file, op);
	else
		print_major_minor(file, op);
	print_time(file);
	(file->file) ? ft_putstr(file->displayname) : ft_putstr(file->name);
	if (file->linkname != NULL)
	{
		ft_putstr(" -> ");
		(void)tab;
		ft_putstr(file->linkname);
	}
	ft_putchar('\n');
	/*
	**if (file->next)
	**ft_putstr("\033[00m");
	*/
	return (file);
}
