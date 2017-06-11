/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 23:51:25 by tbouline          #+#    #+#             */
/*   Updated: 2017/04/22 23:51:29 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void				change_dir(char **old, char *new, int free_needed)
{
	if (*old)
		free(*old);
	*old = ft_strdup(new);
	if (free_needed)
		free(new);
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

int		determine_type(struct stat data)
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
