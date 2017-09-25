/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_hidden.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 02:09:09 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/24 05:44:31 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			ft_checkhiddendir(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] && str[i + 1] == '.' \
			&& str[i + 2] && str[i + 2] != '.')
			return (1);
		i++;
	}
	return (0);
}

int			only_contains_hidden(t_file *start)
{
	char	*path;

	if (ft_checkhiddendir(start->path))
		return (0);
	path = ft_strdup(start->path);
	while (start && ft_strcmp(start->path, path) == 0)
	{
		if (start->name[0] == '.')
			start = start->next;
		else
		{
			free(path);
			path = NULL;
			return (0);
		}
	}
	free(path);
	path = NULL;
	return (1);
}
