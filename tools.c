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

int		determine_type(struct stat *data)
{
	if (S_ISBLK(data->st_mode))
		return (6);
	if (S_ISCHR(data->st_mode))
		return (2);
	if (S_ISDIR(data->st_mode))
		return (4);
	if (S_ISFIFO(data->st_mode))
		return (1);
	if (S_ISLNK(data->st_mode))
		return (10);
	if (S_ISREG(data->st_mode))
		return (8);
	if (S_ISSOCK(data->st_mode))
		return (12);
	else 
		return (0);
}

//Absolute path => pareil que ton get_fname, mais renvoie tout ce qu'il y a avant le 

// t_file				*print_fname(t_file *file, char *entry)
// {
// 	file->name = get_fname(entry);
// 	ft_putstr(file->name);
// 	return (file);
// }

// char				*get_fname(char *entry)
// {
// 	char			*input;
// 	char			*fn;

// 	input = entry;
// 	if (input[(ft_strlen(input) - 1)] == '/')
// 		input[(ft_strlen(input) - 1)] = '\0';
// 	(fn = ft_strrchr(input, '/')) ? ++fn : (fn = input);
// 	return (fn);
// }
//				docs/tiph/dossier/test/file

char		*get_path(char *entry, t_op *op)
{
	int 	i;

	i = ft_strlen(entry);
	while (i > 0)
	{
		if (entry[i - 1] == '/')
		{
			entry[i] = '\0';
			return (entry);
		}
		i--;
	}
	return (ft_strdup(op->origin));
}
