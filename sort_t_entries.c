/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_t_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 05:10:37 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/27 05:10:47 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char 		**sort_t_entry(char **entries, t_op *op)
{
	char 	**wordlist;

	wordlist = ft_sort_ascii_string(entries, op);
	return (wordlist);
}

int 		ft_issort(char **av, t_op *op)
{
	int i;
	int j;

	i = 1;
	j = 2;
	while (av[j])
	{
		if ((op->t == 1 && op->r == 0 && ft_strcmp(av[i], av[j]) > 0)
								||
			(op->t == 1 && op->r == 1 && ft_strcmp(av[i], av[j]) < 0))
			return (0);
		i++;
		j++;
	}
	return (1);
}

char		**ft_sort_time(char **av, t_op *op)
{
	int		i;
	int		j;
	char	*tmp;


	while (ft_issort(av, op) == 0)
	{
		i = 1;
		j = 2;
		while (av[j])
		{
			if ((op->t == 1 && op->r == 0 && ft_strcmp(av[i], av[j]) > 0 && st_mtimes > st_mtimes)
									||
				(op->t == 1 && op->r == 1 && ft_strcmp(av[i], av[j]) < 0))
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
			}
			j++;
			i++;
		}
	}
	return (av);
}
