/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 22:16:43 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/25 21:57:39 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		last_slash(char *origin, int noarg, char *tmp)
{
	int		last_slash;
	int		i;

	last_slash = 0;
	i = 0;
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

char		*store_path(char *entry, t_op *op)
{
	int		i;

	i = ft_strlen(entry);
	while (i > 0)
	{
		if (entry[i - 1] == '/')
		{
			entry[i] = '\0';
			if (entry[0] == '/')
				return (ft_strdup(entry));
			return (ft_strjoin(op->origin, entry));
		}
		i--;
	}
	return (ft_strdup(op->origin));
}

int			write_path(char *path, char *origin, int noarg, int relative)
{
	char	*tmp;

	tmp = ft_strdup(path);
	if (tmp[1] != '\0')
	{
		if (tmp[ft_strlen(tmp) - 1] == '/')
			tmp[ft_strlen(tmp) - 1] = '\0';
	}
	if (ft_strstr(tmp, "../"))
		ft_putstr(ft_strstr(tmp, "../"));
	else if (relative || noarg == 1)
		last_slash(origin, noarg, tmp);
	else
		ft_putstr(tmp);
	ft_putendl(":");
	return (1);
}

int			same_path_everywhere(t_file *file)
{
	while (file->next)
	{
		if (ft_strcmp(file->path, file->next->path))
			return (0);
		file = file->next;
	}
	return (1);
}
