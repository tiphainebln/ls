/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 02:26:13 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/18 13:08:50 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int				ft_issort(char **av, t_op *op)
{
	int			i;
	int			j;
	struct stat data;

	i = 0;
	j = 1;
	data = get_stat(av[i], op);
	while (av[j])
	{
		data = get_stat(av[j], op);
		if (S_ISLNK(data.st_mode))
			op->link = 1;
		if ((op->r == 0 && ft_strcmp(av[i], av[j]) > 0)
								||
			(op->r == 1 && ft_strcmp(av[i], av[j]) < 0))
			return (0);
		i++;
		j++;
	}
	return (1);
}

char			**ft_sort_ascii_string(char **av, t_op *op)
{
	int			i;
	int			j;
	char		*tmp;

	while (ft_issort(av, op) == 0)
	{
		i = 0;
		j = 1;
		while (av[j])
		{
			if ((op->r == 0 && ft_strcmp(av[i], av[j]) > 0)
									||
				(op->r == 1 && ft_strcmp(av[i], av[j]) < 0))
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

char			**sort_entry(char **entries, t_op *op)
{
	char		**wordlist;

	wordlist = ft_sort_ascii_string(entries, op);
	return (wordlist);
}
