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

void				change_dir(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = ft_strdup(new);
}

t_file				*get_directory(char *entry, t_file *file, t_op *op, int sub)
{
	DIR 			*fd;

	if (((fd = opendir(entry))) != NULL)
	{
		if (entry[0] == '/' || sub)
		{
			if (entry[ft_strlen(entry) - 1] == '/')
				change_dir(&op->current, entry);
			else
				change_dir(&op->current, ft_strjoin(entry, "/"));
		}
		else
			change_dir(&op->current, ft_strjoin(ft_strjoin(op->origin, entry), "/"));
		file = read_content(file, fd, op);
		closedir(fd);
	}
	else
		file = new_file(file, op, entry);
	return (file);
}

int					ft_second_to_last(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (--i > 0)
	{
		if (str[i] == '/')
			return (i);
	}
	return (0);
}

int					ft_isitover(t_file *file)
{
	while (file)
	{
		if (file->completed == 0)
			return (0);
		file = file->next;
	}
	return (1);
}	

t_file				*get_sub(t_file *file, t_op *op)
{
	t_file	*curr_dir;

	file = op->begin;
	while (file && ft_strcmp(file->path, op->current))
	{
		ft_putendl(file->path);
		file = file->next;
	}
	curr_dir = file;
	while (file)
	{
		if (file->completed)
		{
			file = file->next;
			if (!file)
			{
				file = curr_dir;
				if (ft_isitover(file))
					return (file);
				while (file && ft_strcmp(ft_strjoin(ft_strjoin(file->path, file->name), "/"), op->current))
					file = file->next;
				file->completed = 1;
				if (ft_strcmp(curr_dir->path, op->current))
					change_dir(&op->current, ft_strjoin(ft_strsub(op->current, 0, ft_second_to_last(op->current)), "/"));
				else
					return (file);
			}
		}
		else if (file->visited)
		{
			while (file && ft_strcmp(file->path, op->current))
				file = file->next;
		}
		else
		{
			file->visited = 1;
			file = get_directory(ft_strjoin(file->path, file->name), file, op, 1);
			file = curr_dir;
		}
	}
	return (file);
}


/* A - Remonter dans current B - Determiner quand un dossier est completed*/

t_file				*read_content(t_file *file, DIR *fd, t_op *op)
{
	struct dirent	*dirent;

	if (!(dirent = (struct dirent *)malloc(sizeof(struct dirent))))
		error(MALLOC_ERROR);
	while (((dirent = readdir(fd)) != NULL))
	{
		file = op->begin;
		file = new_list(file, dirent, op);
	}
	return (file);
	
}

/* 	int				level;

	level = 0;
	file = op->begin;
	while (file)
	{
		//file = op->begin;
		if (file && file->flag == 0 && get_directory(ft_strjoin(op->current, file->name), file, op) == NULL)
			file = op->begin;
		while (file && ft_strcmp(op->current, file->path) != 0)
			file = file->next;
		while (file && file->flag == 1)
			file = file->next;
		while (file && file->flag == 0)
		{
			file = get_directory(ft_strjoin(op->current, file->name), file, op);
			file->completed = 1;
			level++;
		}
	}
	return (file);*/