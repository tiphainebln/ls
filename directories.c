/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 00:17:32 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/28 00:17:34 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file				*get_directories(char *content, t_file *file, t_op *op)
{
	DIR 			*fd;

	if (((fd = opendir(content))) != NULL)
	{
		if (op->current)
			free(op->current);
		//op->current = ft_strjoin(ft_strjoin(current, content), "/");
		op->current = ft_strjoin(ft_strjoin(op->origin, content), "/");
		file = read_content(file, fd, op);
		closedir(fd);
	}
	else
		print_fname(file, op, content);
	return (file);
}
/*
t_file				*get_sub(t_file *file, t_op *op)
{
	file = op->begin;
	ft_putendl("ici");
	while (file)
	{
		file = op->begin;
		while (file && ft_strcmp(op->current, file->path) != 0)
			file = file->next;
		while (file && (file->type != DT_DIR || file->visited))
			file = file->next;
		if (file && file->type == DT_DIR)
		{
			file->visited = 1;
				ft_putendl("la");
			file = get_directories(file->name, op->current, file, op);
		}
		if (file)
			file = file->next;
	}
	return (file);
}
ajouter le flag completed*/
t_file				*read_content(t_file *file, DIR *fd, t_op *op)
{
	struct dirent	*dirent;

	if (!(dirent = (struct dirent *)malloc(sizeof(struct dirent))))
		error(MALLOC_ERROR);
	while (((dirent = readdir(fd)) != NULL))
		file = new_list(file, op);
			print_grp(file);
			print_uid(file);
			print_total(file, op);
			file_type_letter(file);
			print_rights(file);
			print_size(file, op);
			print_links(file, op);
			//long_format(file, op);
	return (file);
	
}
