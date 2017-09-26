/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:41:18 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/18 13:05:05 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int				is_option(char *av, t_op *op)
{
	if (av[1] == 'a' || av[1] == 't' || av[1] == 'r' || av[1] == 'R' ||\
		av[1] == 'l' || av[1] == 'd' || av[1] == '1' || av[1] == 'G')
	{
		op->option = 1;
		return (1);
	}
	else
		op->option = 0;
	return (0);
}

int				does_it_exist(char *av, t_op *op, t_file *file)
{
	char		*fullpath;
	struct stat	data;

	if (av[0] == '/')
		fullpath = ft_strdup(av);
	else
		fullpath = ft_strjoin(op->origin, av);
	if (lstat(fullpath, &data) == -1)
	{
		if (av[0] == '-' && av[1] && av[1] == '-' && !av[2])
		{
			op->doubledash = 1;
			ft_strdel(&fullpath);
			return (0);
		}
		else if (op->error_epur == 1 && is_option(av, op) == 0)
		{
			manage_error(file, OPTION, op, av);
			op->error = ft_strdup(strerror(errno));
		}
		ft_strdel(&fullpath);
		return (0);
	}
	ft_strdel(&fullpath);
	return (1);
}
