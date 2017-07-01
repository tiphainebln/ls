/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 02:13:25 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/26 02:13:27 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

// int 		strfils(char *patha, char *pathb)
// {
// 	int 		i;

// 	i = 0;
// 	while (patha[i] && pathb[i] && patha[i] == pathb[i])
// 		i++;
// 	if (patha[i] == '\0' && pathb[i - 1] == '/')
// 		return (1);
// 	return (0);
// }

// int			cmp_list(t_file *a, t_file *b, int tri)
// {
// 	if (tri == PATH)
// 	{
//         if (a->file || b->file)
//             return (a->file);
//         else if ((a->noarg == b->noarg) && ft_strcmp(a->path, b->path) > 0)
//             return (1);
//         return (0);
// 	}
//     if (tri == REVPATH)
//     {
//         if (a->file || b->file)
//             return (a->file);
//         else if (a->noarg == b->noarg && ft_strcmp(a->path, b->path) < 0 && strfils(a->path, b->path) == 0)
//             return (1);
//         return (0);
//     }
//     if (tri == NAME)
//     {
//         if (a->file && b->file == 0)
//             return (1);
//         else if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) < 0)
//             return (1);
//         else if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) < 0 && ft_strcmp(a->path, b->path) == 0)
//             return (1);
//         return (0);
//     }
// 	if (tri == REVNAME)
// 	{
//         if (a->file && b->file == 0)
//             return (1);
//         else if (a->file && b->file && ft_strcmp(a->displayname, b->displayname) > 0)
//             return (1);
// 		else if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) > 0 && ft_strcmp(a->path, b->path) == 0)
// 			return (1);
// 		return (0);
// 	}
// 	 if (tri == TIME)
//      {
//         if (a->noarg == b->noarg && a->st_mtimes > b->st_mtimes)
//             return (1);
//         else if (a->st_mtimes == b->st_mtimes)
//         {
//             if (ft_strcmp(a->name, b->name) < 0)
//                 return (1);
//             return (0);
//         }
//      }
// 	return (0);
// }

/*
**  explications :
** https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
*/

t_file		*sort(t_file *file, int tri)
{
    t_file *p, *q, *element, *final_list;
    int insize, nmerges, psize, qsize, i;

    /*
     * Silly special case: if `file' was passed in as NULL, return
     * NULL immediately.
     */
    if (!file)
	   return NULL;

    insize = 1;

    while (1)
    {
        p = file;
        file = NULL;
        final_list = NULL;
        nmerges = 0;  /* count number of merges we do in this pass */
        while (p)
        {
        	i = -1;
            nmerges++;  /* there exists a merge to be done */
            /* step `insize' places along from p */
            q = p;
            psize = 0;
            while (++i < insize)
            {
                psize++;
		        q = q->next;
                if (!q)
                    break ;
            }
            /* if q hasn't fallen off end, we have two files to merge */
            qsize = insize;
            /* now we have two files; merge them */
            while (psize > 0 || (qsize > 0 && q))
            {
                /* decide whether next element of merge comes from p or q */
                if (psize == 0)
                {
        		    /* p is empty; e must come from q. */
        		    element = q;
        		    q = q->next;
        		    qsize--;
		        }
                else if (qsize == 0 || !q)
                {
		            /* q is empty; e must come from p. */
		            element = p;
		            p = p->next;
		            psize--;
		        }
                else if (cmp_list(p,q,tri))
                {
        		    /* First element of p is lower (or same);
        		     * e must come from p. */
        		    element = p;
					p = p->next;
					psize--;
        		}
                else
                {
        		    /* First element of q is lower; e must come from q. */
        		    element = q;
        		    q = q->next;
        		    qsize--;
        		}

                /* add the next element to the merged file */
        		if (final_list)
                {
        		    final_list->next = element;
        		}
                else
                {
        		    file = element;
        		}
        		final_list = element;
            }
            /* now p has stepped `insize' places along, and q has too */
            p = q;
        }
	    final_list->next = NULL;

        /* If we have done only one merge, we're finished. */
        if (nmerges <= 1)   /* allow for nmerges==0, the empty file case */
            return file;

        /* Otherwise repeat, merging files twice the size */
        insize *= 2;
    }
}