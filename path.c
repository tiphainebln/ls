/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 22:16:43 by tbouline          #+#    #+#             */
/*   Updated: 2017/04/23 22:16:49 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char		*store_path(char *entry, t_op *op)
{
	int 	i;

	i = ft_strlen(entry);
	while (i > 0)
	{
		if (entry[i - 1] == '/')
		{
			entry[i] = '\0';
			if (entry[0] == '/')
				return (entry);
			return (ft_strjoin(op->origin, entry));
		}
		i--;
	}
	return (ft_strdup(op->origin));
}

void		write_path(char *path, char *origin, int noarg, int relative)
{
	int 		last_slash;
	int 		i;
	char		*tmp;

	last_slash = 0;
	i = 0;
	tmp = ft_strdup(path);
	if (tmp[1] != '\0')
	{
		while(tmp[ft_strlen(tmp) - 1] == '/')
			tmp[ft_strlen(tmp) - 1] = '\0';
	}
	if (ft_strstr(tmp, "../"))
			ft_putstr(ft_strstr(tmp, "../"));
	else if (relative || noarg == 1)
	{
		while (tmp[i] && origin[i] && origin[i] == tmp[i])
		{
			if (tmp[i] == '/')
				last_slash = i;
			i++;
		}
		if (tmp[0] == '/')
			tmp++;
		if (noarg == 1)
			ft_putstr("./");
		ft_putstr(&tmp[last_slash]);
	}
	else
		ft_putstr(tmp);
	ft_putendl(":");
}

int 		same_path_everywhere(t_file *file)
{
	while (file->next)
	{
		if (ft_strcmp(file->path, file->next->path))
			return (0);
		file = file->next;
	}
	return (1);
}
