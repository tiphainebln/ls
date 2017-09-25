/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_t_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 05:10:37 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/25 22:10:57 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

struct stat		get_stat(char *av, t_op *op)
{
	char		*fullpath;
	struct stat this;

	fullpath = NULL;
	if (av[0] == '/')
		fullpath = ft_strdup(av);
	else
		fullpath = ft_strjoin(op->origin, av);
	this = read_links(NULL, op, fullpath, 0);
	ft_strdel(&fullpath);
	return (this);
}

int				ft_issorttime(char **av, t_op *op)
{
	int			i;
	int			j;
	struct stat	data;
	struct stat	log;

	i = 0;
	j = 1;
	while (av[i] && av[j])
	{
		data = get_stat(av[i], op);
		log = get_stat(av[j], op);
		if ((op->t == 1 && op->r == 0 && data.st_mtimespec.tv_sec > \
			log.st_mtimespec.tv_sec) || (op->t == 1 && op->r == 1 && \
			data.st_mtimespec.tv_sec < log.st_mtimespec.tv_sec) || \
			(op->t == 1 && op->r == 1 && data.st_mtimespec.tv_sec == \
			 log.st_mtimespec.tv_sec && ft_strcmp(av[i], av[j]) < 0) || \
			(op->t == 1 && op->r == 0 && data.st_mtimespec.tv_sec == \
			 log.st_mtimespec.tv_sec && ft_strcmp(av[i], av[j]) > 0))
			return (0);
		i++;
		j++;
	}
	return (1);
}

char			**ft_sort_time(char **av, t_op *op)
{
	int			i;
	int			j;
	char		*tmp;
	struct stat	data;
	struct stat	log;

	while (ft_issorttime(av, op) == 0)
	{
		i = 0;
		j = 1;
		while (av[j])
		{
			data = get_stat(av[i], op);
			log = get_stat(av[j], op);
			if ((op->t == 1 && op->r == 0 && data.st_mtimespec.tv_sec > \
			log.st_mtimespec.tv_sec) || (op->t == 1 && op->r == 1 && \
			data.st_mtimespec.tv_sec < log.st_mtimespec.tv_sec) || \
			(op->t == 1 && op->r == 1 && data.st_mtimespec.tv_sec == \
			 log.st_mtimespec.tv_sec && ft_strcmp(av[i], av[j]) < 0) || \
			(op->t == 1 && op->r == 0 && data.st_mtimespec.tv_sec == \
			 log.st_mtimespec.tv_sec && ft_strcmp(av[i], av[j]) > 0))
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

char			**sort_t_entry(char **entries, t_op *op)
{
	char		**wordlist;

	wordlist = ft_sort_time(entries, op);
	return (wordlist);
}
