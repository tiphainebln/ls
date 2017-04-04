/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:50 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/23 03:52:54 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int 		main(int argc, char **argv, char **env)
{
	t_op	*o;
	t_file	*file;
	int 	i;
	int 	(*tab[13])(void);

	init_tab(tab);
	i = 0;
	o = NULL;
	o = init(o, env);
	o = options(argv, o);
	file = NULL;
	while (argv[++i])
	{
		if (argv[i][0] != '-')
			file = get_directory(argv[i], file, o, 0);
		if (argv[i][0] != '-' && o->R)
		 	file = get_sub(file, o);
	}
	file = o->begin;
	if (!file)
	{
		file = get_directory(o->origin, file, o, 0);
		if (o->R)
			file = get_sub(file, o);
	}
	file = o->begin;
	if (o->l)
		print_total(file, o);
	while (file)
	{
		if (opt_a(file, o) == 0)
		{
			file = file->next;
			continue ;
		}
		tab[file->type]();
		if (o->l)
			long_format(file, o);
		else
			ft_putendl(file->name);
		ft_putstr("\033[00m");
		if (o->R && file->next)
		{
			if (ft_strcmp(file->path, file->next->path))
			{
				ft_putchar('\n');
				ft_putendl(ft_strjoin(file->next->path, ":"));
			}
		}
		file = file->next;
	}
	return (0);
}