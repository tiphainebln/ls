/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 20:11:11 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/16 20:11:24 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_op			*init_space(t_op *op)
{
	op->nbuidspace = 0;
	op->nbgrpspace = 0;
	op->nblinkspace = 0;
	op->nbsizespace = 0;
	op->nbmajorspace = 0;
	op->nbminorspace = 0;
	op->rightsize = 0;
	return (op);
}

t_file			*store_space(t_file *file, t_op *op)
{
	file->nbuidspace = op->nbuidspace;
	file->nbgrpspace = op->nbgrpspace;
	file->nblinkspace = op->nblinkspace;
	file->nbsizespace = op->nbsizespace;
	file->nbmajorspace = op->nbmajorspace;
	file->nbminorspace = op->nbminorspace;
	return (file);
}
