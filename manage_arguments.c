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

int			nb_option(char **argv, int size, int i, t_op *op, t_file *file)
{
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] && argv[i][1] == '-' && !argv[i][2] && i == 1)
			op->doubledash = 0;
		else if (argv[i][0] != '-' || !argv[i][1] || does_it_exist(argv[i], op, file) == 1)
			size++;
		i++;
	}
	op->doubledash = 0;
	return (size);
}

char		**epur_args(char **argv, t_op *op, t_file *file)
{
	char 	**epured;
	int 	i;
	int 	size;

	i = 1;
	size = 0;
	size = nb_option(argv, size, i, op, file);
	epured = (char **)malloc(sizeof(char *) * (size + 1));
	i = 1;
	size = 0;
	op->error_epur = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] && argv[i][1] == '-' && !argv[i][2] && i == 1)
			op->doubledash = 0;
		else if (argv[i][0] != '-' || !argv[i][1] || does_it_exist(argv[i], op, file) == 1)
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

t_op		*epur_and_sort(char **argv, t_op *op, t_file *file)
{
	op = options(argv, op, file);
	op->epured = epur_args(argv, op, file);
	if (op->t && *op->epured)
		op->order = sort_t_entry(op->epured, op);
	else if (*op->epured)
		op->order = sort_entry(op->epured, op);
	return (op);
}
