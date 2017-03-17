/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:22:07 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:22:10 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"


t_file					*add_list(struct stat *data, struct dirent *dirent, t_op *op)
{
		t_file			*file;

		file = (t_file *)malloc(sizeof(t_file));
		file->name = ft_strdup(dirent->d_name);
		file->type = dirent->d_type;
		file->st_size = data->st_size;
		file->st_nlink = data->st_nlink;
		file->st_mode = data->st_mode;
		file->st_gid = data->st_gid;
		file->st_uid = data->st_uid;
		file->st_blocks = data->st_blocks;
		file->st_blksize = data->st_blksize;
		file->path = ft_strdup(op->current);
		file->next = NULL;
		file->visited = 0;
		file->completed = 0;
		return (file);
}


t_file					*new_list(t_file *file, t_op *op)
{
	struct stat 		*data;
	struct dirent		*dirent;

	data = (struct stat *)malloc(sizeof(struct stat));
	dirent = (struct dirent *)malloc(sizeof(struct dirent));
	if (stat(ft_strjoin(op->current, dirent->d_name), data) == -1)
		error(ERROR);
	if (!file)
	{
		file = add_list(data, dirent, op);
		op->begin = file;
	}
	else
	{
		while (file->next)
			file = file->next;
		file->next = add_list(data, dirent, op);
	}
	return (file);
}

t_op	*init(t_op *op, char **env)
{
	int 		i;

	i = -1;
	
	if (op == NULL)
	{
		op = (t_op *)malloc(sizeof(t_op));
		op->a = 0;
		op->r = 0;
		op->R = 0;
		op->l = 0;
		op->t = 0;
		op->begin = NULL;
		op->origin = NULL;
		while (env[++i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				op->origin = ft_strjoin(ft_strsub(env[i], 4, ft_strlen(env[i]) - 4), "/");
		}
		op->current = NULL;
		if (op->origin == NULL)
			error(ERROR);
	}
	return (op);
}
