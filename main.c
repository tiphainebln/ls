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

void	write_path(char *path, char *origin, int noarg, int relative)
{
	int 		last_slash;
	int 		i;
	char		*tmp;

	last_slash = 0;
	i = 0;
	tmp = ft_strdup(path);
	tmp[ft_strlen(tmp) - 1] = '\0';
	if (noarg || relative)
	{
		while (tmp[i] && origin[i] && origin[i] == tmp[i])
		{
			if (tmp[i] == '/')
				last_slash = i;
			i++;
		}
		if (tmp[0] == '/')
			tmp++;
		if (noarg == 1)
			ft_putstr("./");
		ft_putendl(ft_strjoin(&tmp[last_slash], ":"));
	}
	else
		ft_putendl(ft_strjoin(tmp, ":"));
}

int 		main(int argc, char **argv, char **env)
{
	t_op	*o;
	t_file	*file;
	int 	i;
	int 	(*tab[13])(void);
	char	*oldpath;
	int 	oldarg;

	init_tab(tab);
	i = 0;
	o = NULL;
	o = init(o, env);
	o = options(argv, o);
	file = NULL;
	oldpath = NULL;
	oldarg = 1;
	if (argc < 0)
		error(ARGUMENT);
	while (argv[++i])
	{
		if (argv[i][0] != '-')
		{
			o->noarg++;
			file = get_directory(argv[i], file, o, 0);
		}
		if (argv[i][0] != '-' && o->R)
		 	file = get_sub(file, o, o->noarg);
	}
	file = o->begin;
	if (o->noarg == 1)
	{
		file = get_directory(o->origin, file, o, 0);
		if (o->R)
			file = get_sub(file, o, o->noarg);
	}
	file = o->begin;
	if (o->l && same_path_everywhere(file))
		print_total(file, o);
	while (file)
	{
		if (opt_a(file, o, argv) == 0)
		{
			if (ft_strcmp(file->name, ".") && only_contains_hidden(file))
			{
				if (oldpath)
					ft_putchar('\n');
				write_path(file->path, o->origin, o->noarg, file->relative);
			}
			file = file->next;
			continue ;
		}
		if (file->noarg != oldarg && o->noarg > 2)
		{
			if (oldpath)
				ft_putchar('\n');
			write_path(file->path, o->origin, o->noarg, file->relative);
			if (o->l)
				print_total(file, o);
		}
		else if (oldpath)
		{
			if (ft_strcmp(file->path, oldpath))
			{
				ft_putchar('\n');
				write_path(file->path, o->origin, o->noarg, file->relative);
				if (o->l)
					print_total(file, o);
			}
		}
		else if (!same_path_everywhere(file))
		{
			if (!o->R || (o->noarg > 2 && file->file == 0))
				write_path(file->path, o->origin, o->noarg, file->relative);
			if (o->l)
				print_total(file, o);
		}
		if (oldpath)
			ft_strdel(&oldpath);
		oldpath = ft_strdup(file->path);
		oldarg = file->noarg;
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

/* when illegal option shut down fucking errythang */
// 1- Integrer un concept de levels pour savoir dissocier le meme dossier passe en argument plusieurs fois. 2- gerer les fichiers proprement
/*
if no arg: remplacer la section "op->origin" par ./, et laisser le reste
if arg relatif (si ca rentre dans le else)
enlever tout
- SEGFAULT -R + fichier
*/