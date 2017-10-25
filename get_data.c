/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 00:28:45 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/24 06:00:34 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char				*get_fname(char *entry)
{
	char			*fn;
	int				i;

	i = ft_strlen(entry) - 1;
	fn = NULL;
	if (entry[i] == '/')
		entry[i] = '\0';
	if ((fn = ft_strrchr(entry, '/')))
		return (ft_strdup(fn + 1));
	else
		return (ft_strdup(entry));
}

t_file				*store_basic(t_file *file, struct stat data)
{
	file->st_size = data.st_size;
	file->st_nlink = data.st_nlink;
	file->st_mode = data.st_mode;
	file->st_gid = data.st_gid;
	file->st_uid = data.st_uid;
	file->st_blocks = data.st_blocks;
	file->st_blksize = data.st_blksize;
	file->st_mtimes = data.st_mtimespec.tv_sec;
	file->st_mntimes = data.st_mtimespec.tv_nsec;
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
	struct group	*grp;
	struct passwd	*uid;

	grp = getgrgid(file->st_gid);
	file->grp = ft_strdup(grp->gr_name);
	uid = getpwuid(file->st_uid);
	if (uid)
		file->uid = ft_strdup(uid->pw_name);
	else
		file->uid = ft_strdup("4389");
	return (file);
}

t_file				*visited_or_completed(t_file *file)
{
	if (file->type == DT_DIR && ft_strcmp(file->name, ".") && \
		ft_strcmp(file->name, ".."))
	{
		file->visited = 0;
		file->completed = 0;
		file->nameasadir = str3join(file->path, file->name, "/");
	}
	else
	{
		file->completed = 1;
		file->visited = 1;
		file->nameasadir = NULL;
	}
	return (file);
}
