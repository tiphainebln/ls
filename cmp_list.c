/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 00:02:49 by tbouline          #+#    #+#             */
/*   Updated: 2017/06/25 00:02:57 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int 		strfils(char *patha, char *pathb)
{
	int 		i;

	i = 0;
	while (patha[i] && pathb[i] && patha[i] == pathb[i])
		i++;
	if (patha[i] == '\0' && pathb[i - 1] == '/')
		return (1);
	return (0);
}

int 		pathsort(t_file *a, t_file *b)
{
	if (a->file || b->file)
		return (a->file);
	else if (a->noarg == b->noarg && ft_strcmp(a->path, b->path) > 0)
		return (1);
	return (0);
}

int 		revpathsort(t_file *a, t_file *b)
{
	if (a->file || b->file)
		return (a->file);
	else if (a->noarg == b->noarg && ft_strcmp(a->path, b->path) < 0 && strfils(a->path, b->path) == 0)
		return (1);
	return (0);
}

int 		namesort(t_file *a, t_file *b)
{
	if (a->file && b->file == 0)
		return (1);
	else if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) < 0)
		return (1);
	else if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) < 0 && ft_strcmp(a->path, b->path) == 0)
		return (1);
	return (0);
}

int 		revnamesort(t_file *a, t_file *b)
{
	if (a->file && b->file == 0)
		return (1);
	else if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) > 0)
		return (1);
	else if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) > 0 && ft_strcmp(a->path, b->path) == 0)
		return (1);
	return (0);
}

int 		pathtimesort(t_file *a, t_file *b)
{
	if (a->file || b->file)
		return (a->file);
	else if (a->noarg == b->noarg && a->foldertime > b->foldertime && strfils(a->path, b->path) == 0)
		return (1);
	return (0);
}

int 		timesort(t_file *a, t_file *b)
{
 	if (a->file && b->file == 0)
		return (1);
    else if (a->noarg == b->noarg && a->foldertime == b->foldertime)
    {
     	if (a->st_mtimes > b->st_mtimes)
     		return (1);
     	else if (a->st_mtimes == b->st_mtimes && a->file && b->file && ft_strcmp(a->displayname, b->displayname) < 0)
     		return (1);
     	else if (a->st_mtimes == b->st_mtimes && ft_strcmp(a->name, b->name) < 0)
     		return (1);
    }
    return (0);
}

int 		revtimesort(t_file *a, t_file *b)
{
	if (a->file ^ b->file)
		return (a->file);
    if (a->noarg == b->noarg && a->st_mtimes < b->st_mtimes && ft_strcmp(a->path, b->path) == 0)
        return (1);
    else if (a->noarg == b->noarg && a->st_mtimes == b->st_mtimes)
    {
        if (ft_strcmp(a->name, b->name) > 0)
            return (1);
    }
    return (0);
}

int 		revpathtimesort(t_file *a, t_file *b)
{
	if (a)
		return (0);
	else if (REVPATHTIME && b)
		return (0);
	else
		return (378);
}

int			cmp_list(t_file *a, t_file *b, int tri)
{
	if (tri == PATH)
		return (pathsort(a, b));
    else if (tri == REVPATH)
    	return (revpathsort(a, b));
    else if (tri == NAME)
    	return (namesort(a, b));
	else if (tri == REVNAME)
		return (revnamesort(a, b));
	else if (tri == PATHTIME)
		return (pathtimesort(a, b));
	else if (tri == REVPATHTIME)
		return (revpathtimesort(a, b));
	else if (tri == TIME)
		return (timesort(a, b));
    else if (tri == REVTIME)
    	return (revtimesort(a, b));
    else
    	return (0);
    //	POUR LE TRI PAR PATH TIME, IL FAUT STOCKER LE TIMESTAMP DES DOSSIERS QUELQUEPART. UN EQUIVALENT DE FILE->PATH QUI SERAIT PLUTOT FILE->FOLDERTIME
    //	POUR CE FAIRE, STOCKER LE STAT OBTENU PAR LE "." DU DIT DOSSIER ME SEMBLE INTELLIGENT.
}