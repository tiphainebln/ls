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

int			cmp_list(t_file *a, t_file *b, int tri)
{
	if (tri == PATH)
	{
		if (a->file || b->file)
			return (a->file);
		else if ((a->noarg == b->noarg) && ft_strcmp(a->path, b->path) > 0)
			return (1);
		return (0);
	}
    if (tri == REVPATH)
    {
    	if (a->file || b->file)
			return (a->file);
		else if (a->noarg == b->noarg && ft_strcmp(a->path, b->path) < 0 && strfils(a->path, b->path) == 0)
			return (1);
		return (0);
    }
    if (tri == NAME)
	{
		if (a->file && b->file == 0)
			return (1);
		else if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) < 0)
			return (1);
		else if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) < 0 && ft_strcmp(a->path, b->path) == 0)
			return (1);
		return (0);
	}
	if (tri == REVNAME)
	{
		if (a->file && b->file == 0)
			return (1);
		else if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) > 0)
			return (1);
		else if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) > 0 && ft_strcmp(a->path, b->path) == 0)
			return (1);
		return (0);
	}
	 if (tri == TIME)
     {
     	if (a->file || b->file)
			return (a->file);
        else if (a->noarg == b->noarg && a->st_mtimes > b->st_mtimes && ft_strcmp(a->path, b->path) == 0)
            return (1);
        else if (a->st_mtimes == b->st_mtimes)
        {
            if (ft_strcmp(a->name, b->name) < 0)
                return (1);
        }
        return (0);
     }
     //st_mtimes_tv_nsec
   //    if (tri == REVTIME)
   //   {
   //   	if (a->file || b->file)
			// return (a->file);
   //      if (a->noarg == b->noarg && a->st_mtimes < b->st_mtimes)
   //          return (1);
   //      else if (a->st_mtimes == b->st_mtimes)
   //      {
   //          if (ft_strcmp(a->name, b->name) < 0)
   //              return (1);
   //      }
   //   }
	return (0);
}