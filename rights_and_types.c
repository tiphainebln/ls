/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:23:44 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:23:57 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		get_suid(t_file *file)
{
	char	c;

	if (file->st_mode & S_ISUID && (file->st_mode & S_IXUSR))
		c = 's';
	else if (file->st_mode & S_ISUID && !(file->st_mode & S_IXUSR))
		c = 'S';
	else if (file->st_mode & S_IXUSR)
		c = 'x';
	else
		c = '-';
	ft_putchar(c);
}

void		get_guid(t_file *file)
{
	char	c;

	if (file->st_mode & S_ISGID && (file->st_mode & S_IXGRP))
		c = 's';
	else if (file->st_mode & S_ISGID && !(file->st_mode & S_IXGRP))
		c = 'S';
	else if (file->st_mode & S_IXGRP)
		c = 'x';
	else
		c = '-';
	ft_putchar(c);
}

void		get_stickybit(t_file *file)
{
	char	c;

	if (file->st_mode & S_ISVTX && (file->st_mode & S_IXOTH))
		c = 't';
	else if (file->st_mode & S_ISVTX && !(file->st_mode & S_IXOTH))
		c = 'T';
	else if (file->st_mode & S_IXOTH)
		c = 'x';
	else
		c = '-';
	ft_putchar(c);
}

int			print_rights(t_file *file)
{
	ft_putchar((file->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWUSR) ? 'w' : '-');
	get_suid(file);
	ft_putchar((file->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWGRP) ? 'w' : '-');
	get_guid(file);
	ft_putchar((file->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWOTH) ? 'w' : '-');
	get_stickybit(file);
	ft_putspaces(file, 0);
	return (0);
}
