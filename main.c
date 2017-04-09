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
		if (noarg)
			ft_putstr(".");
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
		o->noarg = 1;
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
				write_path(file->path, o->origin, o->noarg, file->relative);
			}
			file = file->next;
			continue ;
		}
		if (oldpath)
		{
			if (ft_strcmp(file->path, oldpath))
			{
				ft_putchar('\n');
				write_path(file->path, o->origin, o->noarg, file->relative);
				if (o->l)
					print_total(file, o);
			}
			ft_strdel(&oldpath);
		}
		else if (!same_path_everywhere(file))
		{
			if (!o->R)
				write_path(file->path, o->origin, o->noarg, file->relative);
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

/*
if no arg: remplacer la section "op->origin" par ./, et laisser le reste
if arg relatif (si ca rentre dans le else)
enlever tout
*/

/*
    Si on ordonne laffichage dun dossier cache sans option -a activee, on doit le faire quand meme. 
    On veriefiera si: 1- on est present dans le dossier cache et on a fait un ls sans dossier precise, 2- si argv comporte le nom de ce dossier. 
    Dans ce cas de figure on continue a ne pas afficher les fichiers et dossiers caches, on deroge juste au strstr(file->path, [/.]).
    Il serait intelligent de gerer ca apres avoir transforme les chemins absolus en chemins relatifs. */