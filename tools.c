/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 23:51:25 by tbouline          #+#    #+#             */
/*   Updated: 2017/04/22 23:51:29 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		determine_type(struct stat data)
{
	if (S_ISBLK(data.st_mode))
		return (6);
	if (S_ISCHR(data.st_mode))
		return (2);
	if (S_ISDIR(data.st_mode))
		return (4);
	if (S_ISFIFO(data.st_mode))
		return (1);
	if (S_ISLNK(data.st_mode))
		return (10);
	if (S_ISREG(data.st_mode))
		return (8);
	if (S_ISSOCK(data.st_mode))
		return (12);
	else 
		return (0);
}
