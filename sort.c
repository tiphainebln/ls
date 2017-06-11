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

#define FALSE 0
#define TRUE 1

/*
 * This is the actual sort function. Notice that it returns the new
 * head of the file. (It has to, because the head will not
 * generally be the same t_file after the sort.) So unlike sorting
 * an array, where you can do
 * 
 *     sort(myarray);
 * 
 * you now have to do
 * 
 *     file = filesort(myfile);
 */

// int			cmp_time(t_file *a, t_file *b)
// {
// 	if (a->st_mtimes < b->st_mtimes)
// 		return (a->st_mtimes < b->st_mtimes);
// 	else if (a->st_mtimes == b->st_mtimes)
// 	{
// 		if (a->st_mtimes < b->st_mtimes)
// 			return (a->st_mtimes < b->st_mtimes);
// 		else if (a->st_mtimes == b->st_mtimes)
// 			return (ft_strcmp(a->name, b->name));
// 	}
// 	else
// 		return (1);
// }

t_file		*swap_file(t_file *a, t_file *b)
{
	a->next = b->next;
	b->next = a;
	return (b);
}

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

int			cmp_links(t_file *a, t_file *b, int tri, t_op *op)
{
    if (tri == ENTRY)
    {
        if (a->file)
            return (1);
        if (a->noarg == b->noarg && a->entry && b->entry && ft_strcmp(a->entry, b->entry) > 0)
            return (1);
        return (0);
    }
    if (tri == REVENTRY)
    {
        if (a->file)
            return (1);
        if (a->noarg == b->noarg && a->entry && b->entry && ft_strcmp(a->entry, b->entry) < 0)
            return (1);
        return (0);
    }
	if (tri == PATH)
	{
        if (ft_strcmp(a->path, b->path) > 0)
            return (1);
        if (a->noarg == b->noarg && ft_strcmp(a->path, b->path) > 0)
           return (1);
        return (0);
	}
    if (tri == REVPATH)
    {
        if (a->noarg == b->noarg && ft_strcmp(a->path, b->path) < 0 && ft_strcmp(a->path, op->origin) && strfils(a->path, b->path) == 0)
            return (1);
        return (0);
    }
    if (tri == NAME)
    {
        if (a->file && b->file && ft_strcmp(a->name, b->name) < 0)
            return (1);
        if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) < 0 && ft_strcmp(a->path, b->path) == 0)
            return (1);
        return (0);
    }
	if (tri == REVNAME)
	{
        if (a->file && b->file && ft_strcmp(a->name, b->name) > 0)
            return (1);
		if (a->noarg == b->noarg && ft_strcmp(a->name, b->name) > 0 && ft_strcmp(a->path, b->path) == 0)
			return (1);
		return (0);
	}
	 // if (tri == TIME)
		// cmp_time(a, b);
 	return (0);
}


t_file		*sort(t_file *file, t_op *op, int tri)
{
    t_file *p, *q, *e, *tail;
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
        tail = NULL;
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
        		    e = q;
        		    q = q->next;
        		    qsize--;
		        }
                else if (qsize == 0 || !q)
                {
		            /* q is empty; e must come from p. */
		            e = p;
		            p = p->next;
		            psize--;
		        }
                else if (cmp_links(p,q,tri,op))
                {
        		    /* First element of p is lower (or same);
        		     * e must come from p. */
        		    e = p;
					p = p->next;
					psize--;
        		}
                else
                {
        		    /* First element of q is lower; e must come from q. */
        		    e = q;
        		    q = q->next;
        		    qsize--;
        		}

                /* add the next element to the merged file */
        		if (tail)
                {
        		    tail->next = e;
        		}
                else
                {
        		    file = e;
        		}
        		tail = e;
            }
            /* now p has stepped `insize' places along, and q has too */
            p = q;
        }
	    tail->next = NULL;

        /* If we have done only one merge, we're finished. */
        if (nmerges <= 1)   /* allow for nmerges==0, the empty file case */
            return file;

        /* Otherwise repeat, merging files twice the size */
        insize *= 2;
    }
}