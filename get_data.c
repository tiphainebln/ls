/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 00:28:45 by tbouline          #+#    #+#             */
/*   Updated: 2017/03/26 00:28:47 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file				*store_basic(t_file *file, struct stat *data, t_op *op)
{
		file->st_size = data->st_size;
		file->st_nlink = data->st_nlink;
		file->st_mode = data->st_mode;
		file->st_gid = data->st_gid;
		file->st_uid = data->st_uid;
		file->st_blocks = data->st_blocks;
		file->st_blksize = data->st_blksize;
		file->mtime = data->st_mtime;
		file->path = ft_strdup(op->origin);
		file->next = NULL;
		file->visited = 0;
		file->completed = 0;
		return (file);
}

t_file				*store_groups_uid(t_file *file, t_op *op)
{
	struct group 	*grp;
	struct passwd	*uid;

	grp = (struct group *)malloc(sizeof(struct group));
	uid = (struct passwd *)malloc(sizeof(struct passwd));
	grp = getgrgid(file->st_gid);
	file->grp = ft_strdup(grp->gr_name);
	uid = getpwuid(file->st_uid);
	file->uid = ft_strdup(uid->pw_name);
	return (file);
}