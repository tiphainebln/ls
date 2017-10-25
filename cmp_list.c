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
	if (patha[i] == '\0' && pathb[i - 1] == '/' && pathb[i] != '\0')
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

int 		same_slashes(char *a, char *b)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	while (a[i])
	{
		if (a[i] == '/')
			k++;
		i++;
	}
	while (b[j])
	{
		if (b[j] == '/')
			l++;
		j++;
	}
	if (k == l)
		return (1);
	return (0);
}

int 		roottimesort(t_file *a, t_file *b)
{
	ft_putnbr(a->highestsub);
			ft_putendl(a->path);
			ft_putnbr(b->highestsub);
		ft_putendl(b->path);
		ft_putchar('\n');
	if (a->file || b->file)
		return (a->file);
	else if (a->noarg == b->noarg && strfils(a->path, b->path))
		return (1);
	else if (a->noarg == b->noarg && a->sub == 0 && b->sub)
		return (1);
	else if (a->noarg == b->noarg && a->sub && b->sub == 0)
		return (0);
	else if (a->noarg == b->noarg && a->highestsub && b->highestsub == 0)
		return (1);
	else if (a->noarg == b->noarg && a->highestsub == 0 && b->highestsub)
		return (0);
	else if (a->noarg == b->noarg && a->highestsub && b->highestsub && a->directorytime > b->directorytime)
	{
		// ft_putnbr(a->directorytime);
		// ft_putendl(a->path);
		// ft_putnbr(b->directorytime);
		// ft_putendl(b->path);
		return (1);
	}
	else if (a->noarg == b->noarg && strfils(a->path, b->path) == 0)
	{
		// ft_putendl(a->path);
		// ft_putendl(b->path);
		return (1);
	}
	else
		return (0);
}


int 		pathtimesort(t_file *a, t_file *b)
{
	if (a->file || b->file)
		return (a->file);
	else if (a->noarg == b->noarg && a->sub == 0 && b->sub)
		return (1);
	else if (a->noarg == b->noarg && a->sub && b->sub == 0)
		return (0);
	else if (a->noarg == b->noarg && a->highestsub == 1 && b->highestsub == 1 && a->directorytime > b->directorytime)
		return (1);
	// else if (a->noarg == b->noarg && a->directorytime == b->directorytime && strfils(a->path, b->path) == 0)
	// {
	// 	if (ft_strcmp(a->path, b->path) < 0)
	// 		return (1);
	// }
	return (0);
}

int 		timesort(t_file *a, t_file *b)
{
 	if (a->file && b->file == 0)
		return (1);
    else if (a->noarg == b->noarg && a->directorytime == b->directorytime && ft_strcmp(a->path, b->path) == 0)
    {
     	if (a->st_mtimes > b->st_mtimes)
     		return (1);
     	else if (a->st_mtimes == b->st_mtimes)
		{
			if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) < 0)
				return (1);
			else if (ft_strcmp(a->name, b->name) < 0)
				return (1);
		}
    }
    else if (a->directorytime == b->directorytime && ft_strcmp(a->path, b->path) == 0)
    {
     	if (a->st_mtimes > b->st_mtimes)
     		return (1);
     	else if (a->st_mtimes == b->st_mtimes)
		{
			if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) < 0)
				return (1);
			else if (ft_strcmp(a->name, b->name) < 0)
				return (1);
		}
	}
    return (0);
}

int 		revtimesort(t_file *a, t_file *b)
{
	if (a->file ^ b->file)
		return (a->file);
	else if (a->noarg == b->noarg && a->foldertime == b->foldertime && ft_strcmp(a->path, b->path) == 0)
	{
		if (a->st_mtimes < b->st_mtimes)
			return (1);
		else if (a->st_mtimes == b->st_mtimes)
		{
			if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) > 0)
				return (1);
			else if (ft_strcmp(a->name, b->name) > 0)
				return (1);
		}
	}
	return (0);
}
int 		revpathtimesort(t_file *a, t_file *b)
{
	if (a->file || b->file)
		return (a->file);
	else if (a->noarg == b->noarg && a->foldertime > b->foldertime && ft_strcmp(a->path, b->path) > 0 && strfils(a->path, b->path) == 0)
		return (1);
	return (0);
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
	else if (tri == TIME)
		return (timesort(a, b));
    else if (tri == REVTIME)
    	return (revtimesort(a, b));
    else if (tri == PATHTIME)
		return (pathtimesort(a, b));
    else if (tri == REVPATHTIME)
		return (revpathtimesort(a, b));
	else if (tri == ROOTTIME)
		return (roottimesort(a, b));
    else
    	return (0);
}