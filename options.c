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

void		select_options(char *argv, t_op *op, int j)
{
	if (argv[j] == 'a' && op->a == 0)
		op->a++;
	else if (argv[j] == 't' && op->t == 0)
		op->t++;
	else if (argv[j] == 'r' && op->r == 0)
		op->r++;
	else if (argv[j] == 'R' && op->R == 0)
		op->R++;
	else if (argv[j] == 'l' && op->l == 0)
		op->l++;
	else if (argv[j] == 'd' && op->d == 0)
		op->d++;
	else if (argv[j] == '1' && op->un == 0)
		op->un++;
	else if (argv[j] == 'G' && op->G == 0)
		op->G++;
	else
		manage_error(NULL, OPTION, op, &argv[j]);
}

t_op		*get_options(char *argv, t_op *op)
{
	int		j;

	j = 1;
	while (argv[j])
	{
		select_options(argv, op, j);
		j++;
	}
	if (!op->d && !op->a && !op->t && !op->r && !op->R && !op->l && !op->un\
		&& !op->G)
		manage_error(NULL, OPTION, op, &argv[1]);
	return (op);
}

t_op		*options(char **argv, t_op *op, t_file *file)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (i == 0 && argv[i][0] == '-' && argv[i][1] && argv[i][1] == '-' \
			&& !argv[i][2])
			continue ;
		else if (argv[i][0] == '-' && argv[i][1] && argv[i][1] != '-' && \
			does_it_exist(argv[i], op, file) == 0)
			op = get_options(argv[i], op);
	}
	return (op);
}
