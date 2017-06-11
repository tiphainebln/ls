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
	// if (file->next)
	// // ft_putstr("\033[00m");
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
	else if (choice == 4)
		space = op->nbmajorspace - ft_intlen(file->major);
	else if (choice == 5)
		space = op->nbminorspace - ft_intlen(file->minor);
	else
		space = op->nblinkspace - ft_intlen(file->st_nlink);
	if (choice != 2)
		ft_putstr("  ");
	while (--space >= 0)
		ft_putchar(' ');
}
