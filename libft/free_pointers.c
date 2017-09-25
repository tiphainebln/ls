/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 06:00:53 by tbouline          #+#    #+#             */
/*   Updated: 2016/12/12 06:01:12 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**free_pointers(char **pointer)
{
	int		i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		pointer[i++] = NULL;
	}
	free(pointer);
	pointer = NULL;
	return (pointer);
}
