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

int 		ft_checkhiddendir(char *str)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] && str[i + 1] == '.' && str[i + 2] && str[i + 2] != '.')
			return (1);
		i++;
	}
	return (0);
}

int 		only_contains_hidden(t_file *start)
{
	char	*path;

	if (ft_checkhiddendir(start->path))
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

t_file		*first_things_first(t_file *file)
{
	t_file	*begin;
	char	*oldpath;

	begin = file;
	oldpath = NULL;
	file->first = 1;
	while (file)
	{
		oldpath = ft_strdup(file->path);
		file = file->next;
		if (file)
		{
			if (ft_strcmp(file->path, oldpath) == 0)
				file->first = 0;
			else
				file->first = 1;
		}
		ft_strdel(&oldpath);
	}
	file = begin;
	return (file);
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
	if (argc > 1)
		o = options(argv, o);
	file = NULL;
	oldpath = NULL;
	oldarg = 1;
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
	if (!file)
		manage_error(file, NOTHINGTODO, o, NULL);
	file = o->begin;
	if (o->r)
	{
		file = sort(file, o, REVPATH);
		file = sort(file, o, REVERSE);
	}
	else
	{
		file = sort(file, o, PATH);
		file = sort(file, o, NAME);
	}
	o->begin = file;
	if (o->l && same_path_everywhere(file) && file->file == 0)
		print_total(file, o);
	file = first_things_first(file);
	while (file)
	{
		if (opt_a(file, o, argv) == 0)
		{
			if (ft_strcmp(file->name, ".") && only_contains_hidden(file) && ft_strcmp(file->path, oldpath))
			{
				if (oldpath)
					ft_putchar('\n');
				write_path(file->path, o->origin, o->noarg, file->relative);
			}
			file = file->next;
			continue ;
		}
		else if (file->noarg != oldarg && o->noarg > 2)
		{
			if (oldpath)
				ft_putchar('\n');
			if (file->file == 0)
				write_path(file->path, o->origin, o->noarg, file->relative);
			if (o->l && file->file == 0)
				print_total(file, o);
		}
		else if (oldpath)
		{
			if (ft_strcmp(file->path, oldpath))
			{
				ft_putchar('\n');
				if (file->file == 0)
					write_path(file->path, o->origin, o->noarg, file->relative);
				if (o->l && file->file == 0)
					print_total(file, o);
			}
		}
		else if (!same_path_everywhere(file))
		{
			if (!o->R || (o->noarg > 2 && file->file == 0))
				write_path(file->path, o->origin, o->noarg, file->relative);
			if (o->l && file->file == 0)
				print_total(file, o);
		}
		if (oldpath)
			ft_strdel(&oldpath);
		oldpath = ft_strdup(file->path);
		oldarg = file->noarg;
		//tab[file->type]();
		if (o->l)
			long_format(file, o, tab);
		else
			(file->file) ? ft_putendl(file->displayname) : ft_putendl(file->name);
		// ft_putstr("\033[00m");
		file = file->next;
	}
	if (oldpath)
		ft_strdel(&oldpath);
	manage_error(file, NOTHINGTODO, o, NULL);
	return (0);
}

/* 
** - data->m_time = structure.st_mtimespec;
** - test dans /dev pourquoi type_rights ne fonctionne pas avec fd ? 
** - decouper le main en petites fonctions -> parse // -> affichage
** - tri par temps
** - lien symbolique supprime.
** - lien stnbolique dans un dossier, file->realtype n'est pas set
** http://faculty.salina.k-state.edu/tim/CMST302/study_guide/topic7/bubble.html   -> revoir logique
** - affichage de stderr->fd/0 etc.. a decaler par rapport a l'emplacement des majors/minors
** https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.c
** - affichage des noms a revoir : des que deux fichiers situes a la racine sont passes en parametres ne pas mettre d'espaces
** Affichage de deux fois le meme dossier
** dossiers vides ne se printent pas quand je fais ./ft_ls -Rr TEST abc .. Mais sinon comportement identique. J'ASSURE :)
** Commencer à réfléchir au fameux maillon d'erreur
*/
