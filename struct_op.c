/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:47:27 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/18 13:00:21 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_op		*data_op(t_op *op)
{
	op->a = 0;
	op->r = 0;
	op->R = 0;
	op->l = 0;
	op->t = 0;
	op->d = 0;
	op->un = 0;
	op->G = 0;
	op->begin = NULL;
	op->origin = NULL;
	op->nbsizespace = 0;
	op->nblinkspace = 0;
	op->nbgrpspace = 0;
	op->nbuidspace = 0;
	op->nbminorspace = 0;
	op->nbmajorspace = 0;
	op->noarg = 1;
	op->relative = 0;
	op->linkname = NULL;
	op->link = 0;
	op->latest = NULL;
	op->error_epur = 0;
	op->option = 0;
	return (op);
}

t_op		*init(t_op *op, char **env)
{
	int		i;

	i = -1;
	if (op == NULL)
	{
		op = (t_op *)malloc(sizeof(t_op));
		op = data_op(op);
		while (env[++i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				op->origin = ft_strjoin(&env[i][4], "/");
		}
		op->current = NULL;
		op->error = NULL;
		op->entry = NULL;
		op->order = NULL;
		op->doubledash = 0;
		op->theresbeenamistake = 0;
		if (op->origin == NULL)
			manage_error(NULL, ERROR, op, NULL);
	}
	return (op);
}
