/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subs_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 23:06:51 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/18 12:59:39 by tbouline         ###   ########.fr       */
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

char				*father(char *current)
{
	char			*father;
	char			*mother;

	father = ft_strsub(current, 0, ft_second_to_last(current));
	mother = ft_strjoin(father, "/");
	free(father);
	return (mother);
}
