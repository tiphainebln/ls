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

t_file				*store_basic(t_file *file, struct stat data)
{
		file->st_size = data.st_size;
		file->st_nlink = data.st_nlink;
		file->st_mode = data.st_mode;
		file->st_gid = data.st_gid;
		file->st_uid = data.st_uid;
		file->st_blocks = data.st_blocks;
		file->st_blksize = data.st_blksize;
		file->st_mtimes = data.st_mtime;
		if (S_ISBLK(file->st_mode) || S_ISCHR(file->st_mode))
		{
			file->major = major(data.st_rdev);
			file->minor = minor(data.st_rdev);
		}
		else
		{
			file->minor = -1;
			file->major = -1;
		}
		file->next = NULL;
		return (file);
}

t_file				*store_groups_uid(t_file *file)
{
	struct group 	*grp;
	struct passwd	*uid;

	grp = getgrgid(file->st_gid);
	file->grp = ft_strdup(grp->gr_name);
	uid = getpwuid(file->st_uid);
	file->uid = ft_strdup(uid->pw_name);
	return (file);
}

int 				valuemax(int size, t_op *op, char *name, int origin)
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

t_file				*nb_spaces(t_file *file, t_op *op)
{
	if (op->nbuidspace < ft_strlen(file->uid))
		op->nbuidspace = valuemax(ft_strlen(file->uid), op, file->name, op->nbuidspace);
	if (op->nbgrpspace < ft_strlen(file->grp))
		op->nbgrpspace = valuemax(ft_strlen(file->grp), op, file->name, op->nbgrpspace);
	if (op->nblinkspace < ft_intlen(file->st_nlink))
		op->nblinkspace = valuemax(ft_intlen(file->st_nlink), op, file->name, op->nblinkspace);
	if (op->nbsizespace < ft_intlen(file->st_size))
		op->nbsizespace = valuemax(ft_intlen(file->st_size), op, file->name, op->nbsizespace);
	if (file->major != -1 && op->nbmajorspace < ft_intlen(file->major))
		op->nbmajorspace = valuemax(ft_intlen(file->major), op, file->name, op->nbmajorspace);
	if (file->minor != -1 && op->nbminorspace < ft_intlen(file->minor))
		op->nbminorspace = valuemax(ft_intlen(file->minor), op, file->name, op->nbminorspace);
	return (file);
}