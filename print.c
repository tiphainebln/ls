/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:15:20 by tbouline          #+#    #+#             */
/*   Updated: 2017/05/13 22:15:23 by tbouline         ###   ########.fr       */
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

void				print_major_minor(t_file *file, t_op *op)
{
	ft_putspaces(file, op, 4);
	ft_putnbr(file->major);
	ft_putstr(",");
	ft_putspaces(file, op, 5);
	ft_putnbr(file->minor);
	ft_putstr(" ");
}

char				*get_fname(char *entry)
{
	char			*fn;
	int 			i;

	i = ft_strlen(entry) - 1;
	fn = NULL;
	if (entry[i] == '/')
		entry[i] = '\0';
	if ((fn = ft_strrchr(entry, '/')))
		return (ft_strdup(fn + 1));
	else
		return (ft_strdup(entry));;
}