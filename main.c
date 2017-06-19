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

t_file		*sort_lst(t_file *file, t_op *op)
{
	file = op->begin;
	if (op->r)
	{
		file = sort(file, REVPATH);
		file = sort(file, REVNAME);
	}
	else
	{
		file = sort(file, PATH);
		file = sort(file, NAME);
	}
	return (file);
}

int 		ft_issort(char **av, t_op *op)
{
	int i;
	int j;

	i = 1;
	j = 2;
	while (av[j])
	{
		if ((op->r == 0 && ft_strcmp(av[i], av[j]) > 0)
								||
			(op->r == 1 && ft_strcmp(av[i], av[j]) < 0))
			return (0);
		i++;
		j++;
	}
	return (1);
}

char		**ft_sort_ascii_string(char **av, t_op *op)
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

char 		**sort_entry(char **entries, t_op *op)
{
	char 	**wordlist;

	wordlist = ft_sort_ascii_string(entries, op);
	return (wordlist);
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
		o = options(argv, o);
	file = NULL;
	oldpath = NULL;
	oldarg = 1;
	o->order = sort_entry(argv, o);
	while (o->order[i])
	{
		if (o->order[i][0] != '-')
		{
			o->noarg++;
			file = get_directory(o->order[i], file, o, 0);
		}
		if (o->order[i][0] != '-' && o->R)
		 	file = get_sub(file, o, o->noarg);
		i++;
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
** - lien symbolique supprime.
** - lien stnbolique dans un dossier, file->realtype n'est pas set
** http://faculty.salina.k-state.edu/tim/CMST302/study_guide/topic7/bubble.html   -> revoir logique
** - affichage de stderr->fd/0 etc.. a decaler par rapport a l'emplacement des majors/minors
** https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.c
** dossiers vides ne se printent pas quand je fais ./ft_ls -Rr TEST abc .. Mais sinon comportement identique. J'ASSURE :)
** Commencer à réfléchir au fameux maillon d'erreur
** ADD FILE A COMPLETER
** couleurs -> identiques au ls ? 
** ./ft_ls -R sorttest TESTDIR ----> le tri se fait dans l'ordre des arguments passes en parametre
** ➜  ft_ls git:(master) ✗ ./ft_ls -Rr ! Makefile auteur ~/chmod.c auteur TEST auteur TEST ! !
** [1]    38401 segmentation fault  ./ft_ls -Rr ! Makefile auteur ~/chmod.c auteur TEST auteur TEST ! !
** fix l'affichage du path
** tri en reverse a finir : ./ft_ls -Rr Makefile !  auteur ~/chmod.c auteur TEST auteur TEST !
** ls -R1 abc f ! d ! Makefile norights -----> les maillons d'erreurs doivent etre tries 
** [1]    68805 segmentation fault  ./ft_ls -R
*/
