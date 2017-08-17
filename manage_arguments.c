/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 16:13:33 by tbouline          #+#    #+#             */
/*   Updated: 2017/08/11 16:13:35 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			no_option(char **argv, int size, int i)
{
	while (argv[i])
	{
		if (argv[i][0] != '-' || !argv[i][1])
			size++;
		i++;
	}
	return(size);
}

char		**epur_args(char **argv)
{
	char 	**epured;
	int 	i;
	int 	size;

	i = 1;
	size = 0;
	size = no_option(argv, size, i);
	epured = (char **)malloc(sizeof(char *) * (size + 1));
	i = 1;
	size = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-' || !argv[i][1])
		{
			epured[size] = ft_strdup(argv[i]);
			size++;
		}
		i++; 
	}
	i = 0;
	epured[size] = NULL;
	return (epured);
}

t_op		*epure_and_sort(char **argv, t_op *op)
{
	op = options(argv, op);
	op->epured = epur_args(argv);
	if (op->t && *op->epured)
		op->order = sort_t_entry(op->epured, op);
	else if (*op->epured)
		op->order = sort_entry(op->epured, op);
	return (op);
}
