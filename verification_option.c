/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:41:18 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/27 16:41:21 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		is_option(char *argv)
{
	if (argv[1] == 'a' || argv[1] == 't' || argv[1] == 'r' || argv[1] == 'R' || \
		argv[1] == 'l' || argv[1] == 'd' || argv[1] == '1')
		return (1);
	return (0);
}

int		does_it_exist(char *argv, t_op *op, t_file *file)
{
	char 			*fullpath;
	struct stat 	data;

	fullpath = NULL;
	if (argv[0] == '/')
		fullpath = ft_strdup(argv);
	else
		fullpath = ft_strjoin(op->origin, argv);
	if (lstat(fullpath, &data) == -1)
	{
		if (op->error_epur == 1 && is_option(argv) == 0)
		{
			manage_error(file, ARGUMENT, op, argv);
			op->error = ft_strdup(strerror(errno));
		}
		return (0);
	}
	ft_strdel(&fullpath);
	return (1);
}
