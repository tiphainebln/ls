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

int				print_rights(t_file *file)
{
	ft_putchar((file->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(' ');
	return (0);

}

int 			file_type_letter(t_file *file)
{
    char  	  c;

    if (S_ISREG(file->st_mode))
        c = '-';
    else if (S_ISDIR(file->st_mode))
        c = 'd';
    else if (S_ISBLK(file->st_mode))
        c = 'b';
    else if (S_ISCHR(file->st_mode))
        c = 'c';
    else if (S_ISFIFO(file->st_mode))
        c = 'p';
    else if (S_ISLNK(file->st_mode))
        c = 'l';
    else if (S_ISSOCK(file->st_mode))
        c = 's';
    else
    	c = '?';
	ft_putchar(c);
    return(c);
}


t_file				*print_total(t_file *file, t_op *op)
{
	int				total;

	total = 0;
	while (file != NULL)
	{
		total += file->st_blocks;
		file = file->next;
	}
	if (total > 0)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	return (file);
}

char				*print_fname(char *entry)
{
	char			*input;
	char			*fn;

	input = entry;
	if (input[(ft_strlen(input) - 1)] == '/')
		input[(ft_strlen(input) - 1)] = '\0';
	(fn = ft_strrchr(input, '/')) ? ++fn : (fn = input);
	// ft_putstr(fn);
	// ft_putchar('\n');
	return (fn);
}