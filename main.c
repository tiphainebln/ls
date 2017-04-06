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

int 		only_contains_hidden(t_file *start)
{
	char	*path;

	if (ft_strstr(start->path, "/."))
		return (0);
	path = ft_strdup(start->path);
	while (start && ft_strcmp(start->path, path) == 0)
	{
		if (start->name[0] == '.')
			start = start->next;
		else
		{
			free(path);
			path = NULL;
			return (0);
		}
	}
	free(path);
	path = NULL;
	return (1);
}

int 		same_path_everywhere(t_file *file)
{
	while (file->next)
	{
		if (ft_strcmp(file->path, file->next->path))
			return (0);
		file = file->next;
	}
	return (1);
}

int 		main(int argc, char **argv, char **env)
{
	t_op	*o;
	t_file	*file;
	int 	i;
	int 	(*tab[13])(void);
	char	*oldpath;

	init_tab(tab);
	i = 0;
	o = NULL;
	o = init(o, env);
	o = options(argv, o);
	file = NULL;
	oldpath = NULL;
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
	if (o->l && same_path_everywhere(file))
		print_total(file, o);
	while (file)
	{
		if (opt_a(file, o) == 0)
		{
			if (ft_strcmp(file->name, ".") && only_contains_hidden(file))
			{
				if (oldpath)
					ft_putchar('\n');
				ft_putendl(ft_strjoin(file->path, ":"));
			}
			file = file->next;
			continue ;
		}
		if (oldpath)
		{
			if (ft_strcmp(file->path, oldpath))
			{
				ft_putchar('\n');
				ft_putendl(ft_strjoin(file->path, ":"));
				if (o->l)
					print_total(file, o);
			}
			ft_strdel(&oldpath);
		}
		else if (!same_path_everywhere(file))
		{
			if (!o->R)
				ft_putendl(ft_strjoin(file->path, ":"));
			if (o->l)
				print_total(file, o);
		}
		oldpath = ft_strdup(file->path);
		tab[file->type]();
		if (o->l)
			long_format(file, o);
		else
			ft_putendl(file->name);
		ft_putstr("\033[00m");
		file = file->next;
	}
	return (0);
}