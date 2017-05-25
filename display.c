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

int 			ft_cmppostorigin(char *origin, char *path, int free_needed)
{
	int 		i;

	i = 0;
	while (origin[i] && path[i] && origin[i] == path[i])
		i++;
	if (path[i])
	{
		if (ft_strstr(&path[i - 1], "/."))
		{
			if (free_needed)
				free(origin);
			return (0);
		}
	}
	if (free_needed)
		free(origin);
	return (1);
}

int 			relative_hiddenry(t_file *file, t_op *op, char **argv)
{
	int 	i;
	int 	j;
	char	*fullpath;

	i = 1;
	j = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			j++;
		if (j == file->noarg)
			break ;
		i++;
	}
	if (argv[i][0] == '/')
		return (ft_cmppostorigin(argv[i], file->path, 0));
	else
	{
		fullpath = ft_strjoin(op->origin, argv[i]);
		return (ft_cmppostorigin(fullpath, file->path, 1));
	}
} 

int 			opt_a(t_file *file, t_op *op, char **argv)
{
	if (op->a)
		return (1);
	if (file->name[0] == '.')
		return (0);
	if (ft_strstr(file->path, "/."))
	{
		if (op->noarg == 1 && ft_strstr(op->origin, "/."))
		{
			if (!op->R)
				return (1);
			else
				return (ft_cmppostorigin(op->origin, file->path, 0));
		}
		else if (op->noarg > 1 && ft_strstr(file->path, "/."))
			return (relative_hiddenry(file, op, argv));
		else
			return (0);
	}
	return (1);
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
		tab[file->typereal]();
		ft_putstr(file->linkname);
	}
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
