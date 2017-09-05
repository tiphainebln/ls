/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:17:07 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:17:09 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_op		*get_options(char *argv, t_op *o)
{
	int		j;

	j = 1;
	while (argv[j])
	{
		if (argv[j] == 'a' && o->a == 0)
			o->a++;
		else if (argv[j] == 't' && o->t == 0)
			o->t++;
		else if (argv[j] == 'r' && o->r == 0)
			o->r++;
		else if (argv[j] == 'R' && o->R == 0)
			o->R++;
		else if (argv[j] == 'l' && o->l == 0)
			o->l++;
		else if (argv[j] == 'd' && o->d == 0)
			o->d++;
		else if (argv[j] == '1' && o->un == 0)
			o->un++;
		else
			manage_error(NULL, OPTION, o, argv);
		j++;
	}
	if (!o->d && !o->a && !o->t && !o->r && !o->R && !o->l && !o->un)
		manage_error(NULL, OPTION, o, argv);
	return (o);
}

t_op		*options(char **argv, t_op *o, t_file *file)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (i == 0 && argv[i][0] == '-' && argv[i][1] && argv[i][1] == '-' && !argv[i][2])
			continue ;
		else if (argv[i][0] == '-' && argv[i][1] && argv[i][1] != '-' && does_it_exist(argv[i], o, file) == 0)
			o = get_options(argv[i], o);
	}
	return (o);
}
