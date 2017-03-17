/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 04:35:01 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/27 04:35:02 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_op		*recursive(file *file, struct dirent *dirent, t_op *op)
{
	get_directories(content, file)
	if (op->R == 1)
	{
		if (dirent->d_type == DT_DIR && ft_strcmp(file->name, "..") != 0 && \
			ft_strcmp(file->name, "..") != 0)
		{
			ft_putstr(file->name);
			recursive(file, dirent, op);
		}
	}
	return (o);
}