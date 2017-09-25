/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 23:51:25 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/15 15:49:09 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			determine_type(struct stat data)
{
	if (S_ISBLK(data.st_mode))
		return (6);
	if (S_ISCHR(data.st_mode))
		return (2);
	if (S_ISDIR(data.st_mode))
		return (4);
	if (S_ISFIFO(data.st_mode))
		return (1);
	if (S_ISLNK(data.st_mode))
		return (10);
	if (S_ISREG(data.st_mode))
		return (8);
	if (S_ISSOCK(data.st_mode))
		return (12);
	else
		return (0);
}

void		print_type_letter(t_file *file)
{
	char	c;

	if (file->type == 8)
		c = '-';
	else if (file->type == 4)
		c = 'd';
	else if (file->type == 6)
		c = 'b';
	else if (file->type == 2)
		c = 'c';
	else if (file->type == 1)
		c = 'p';
	else if (file->type == 10)
		c = 'l';
	else if (file->type == 12)
		c = 's';
	else
		c = '?';
	ft_putchar(c);
}
