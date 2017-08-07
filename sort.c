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