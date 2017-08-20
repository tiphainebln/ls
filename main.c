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
	i = 0;
	o = NULL;
	o = init(o, env);
	if (argc > 1)
		epure_and_sort(argv, o);
	file = NULL;
	oldpath = NULL;
	oldarg = 1;
	while (o->order && o->order[i])
	{
		o->error_happened = 0;
		o->noarg++;
		file = get_directory(o->order[i], file, o, 0);
		if (o->R && o->error_happened == 0)
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
	file = inject_time(file, o);
	file = space_central(file, o);
	if (!file)
		manage_error(file, NOTHINGTODO, o, NULL);
	file = sort_lst(file, o);
	o->begin = file;
	if (o->l && same_path_everywhere(file) && file->file == 0)
		print_total(file, o);
	file = first_things_first(file);
	if (o->d == 0)
		display_path(file, o, o->order, tab);
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
** le tri par entry par temps est a faire differement : apres les get_dir, faire une nouvelle fonction de tri par entry pour le temps :)
** a partir de la, le tri avec -Rt devrait marcher :))
** -rt a faire + path -t
** ** ./ft_ls Rt ne fonctionne pas
** 05/08 -rt réparé, entry rt a faire fontionner maintenant.


DONE = 
-segfault ft_ls - ..truc corrigé (op_a)
-boucle infinie sort -t argument corrigé
-tri path time sur la bonne voie
-separation du display ls et du display path

FUNCT 1 ====> ESPACEMENTS ENTRE GROUPE/SIZE, GROUPE/MAJORMINORS, MINOR/MAJOR A GERER QUAND CHANGEMENT DE DOSSIERS
piste 1 = creer une liste chainée qui contiendra les espaces de chaque elements.
piste 2 = lorsque le path change, on recupere le plus grand nombre d'espaces du dossier et on l'applique a l'ensemble des espaces des elements du dossier.
piste 3 = while (on est sur le meme dossier)
		  on applique les espaces --->>> utiliser oldpath??

FUNCT 2 =====> FONTIONS PATHTIME ET REVPATHTIME A FAIRE
piste 1 = encore quelques ajustements a faire : pas de doublons, les sous-dossiers doivent etre de pair avec leur dossier d'origine
piste 2 = timesort et pathtimesort se complètent, pathtime devrait etre bon miantenant il faut ajuster timesort !

FUNCT 3 =====> SORT TIME ENTRIES A CORRIGER
edit : les majuscules doivent toujours etre devant !!!

FUNCT 4 =====> FONTION REVTIME !!!

petits trucs a corriger : 

---> ./ft_ls -r auteur Makefile ../chmod.c 
---> - -- --- passes en parametre

BONUS   ======>  ****  trier toute l'arborescence   ****
				- priorités a get_data et storage, leurs donner un sens et bien separer ->o et ->file
		======>   ****  bien relire et comprendre le tri ****
				- https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
		======>   ****   option couleur   ****
				- répliquer ls

*/
