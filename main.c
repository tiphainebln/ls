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
	i = 1;
	o = NULL;
	o = init(o, env);
	if (argc > 1)
	{
		o = options(argv, o);
		o->order = sort_entry(argv, o);
	}
	file = NULL;
	oldpath = NULL;
	oldarg = 1;
	while (o->order && o->order[i])
	{
		o->error_happened = 0;
		if (o->order[i][0] != '-')
		{
			o->noarg++;
			file = get_directory(o->order[i], file, o, 0);
		}
		if (o->order[i][0] != '-' && o->R && o->error_happened == 0)
		 	file = get_sub(file, o, o->noarg, NULL);
		i++;
	}
	file = o->begin;
	if (o->noarg == 1)
	{
		file = get_directory(o->origin, file, o, 0);
		if (o->R)
			file = get_sub(file, o, o->noarg, NULL);
	}
	if (!file)
		manage_error(file, NOTHINGTODO, o, NULL);
	//if (o->t)
		//o->order = sort_t_entry(argv, o);
	file = sort_lst(file, o);
	o->begin = file;
	if (o->l && same_path_everywhere(file) && file->file == 0)
		print_total(file, o);
	file = first_things_first(file);
	display_path(file, o, argv, tab);
	if (oldpath)
		ft_strdel(&oldpath);
	manage_error(file, NOTHINGTODO, o, NULL);
	return (0);
}

/* 
** - data->m_time = structure.st_mtimespec;
** - decouper le main en petites fonctions -> parse // -> affichage
** - tri par temps
** http://faculty.salina.k-state.edu/tim/CMST302/study_guide/topic7/bubble.html   -> revoir logique
** - affichage de stderr->fd/0 etc.. a decaler par rapport a l'emplacement des majors/minors
** https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.c
** espacements entre groupes et size, groupes et minor/major et minor/major a gerer
** arborescence a revoir !!! 
** bien relire et comprendre le tri a fusion, schematisé comment il impacte la liste chainee, renommer les variables de façon comprehensible :)
** ./ft_ls Rt !!!!!
** le tri par entry par temps est a faire differement : apres les get_dir, faire une nouvelle fonction de tri par entry pour le temps :)
** a partir de la, le tri avec -Rt devrait marcher :))
*/
