/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:55:17 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/10 15:55:19 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int				valuemax(int size, t_op *op, char *name, int origin)
{
	if (name[0] == '.')
	{
		if (op->a)
			return (size);
		else
			return (origin);
	}
	return (size);
}

t_file			*nb_spaces(t_file *file, t_op *op)
{
	if (op->nbuidspace < ft_strlen(file->uid))
		op->nbuidspace = valuemax(ft_strlen(file->uid), op, \
			file->name, op->nbuidspace);
	if (op->nbgrpspace < ft_strlen(file->grp))
		op->nbgrpspace = valuemax(ft_strlen(file->grp), op, \
			file->name, op->nbgrpspace);
	if (op->nblinkspace < ft_intlen(file->st_nlink))
		op->nblinkspace = valuemax(ft_intlen(file->st_nlink), op, \
			file->name, op->nblinkspace);
	if (op->nbsizespace < ft_intlen(file->st_size))
		op->nbsizespace = valuemax(ft_intlen(file->st_size), op, \
			file->name, op->nbsizespace);
	if (file->major != -1 && op->nbmajorspace < ft_intlen(file->major))
		op->nbmajorspace = valuemax(ft_intlen(file->major), op, \
			file->name, op->nbmajorspace);
	if (file->minor != -1 && op->nbminorspace < ft_intlen(file->minor))
		op->nbminorspace = valuemax(ft_intlen(file->minor), op, \
			file->name, op->nbminorspace);
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
