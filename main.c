/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:50 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/23 03:52:54 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int 		main(int argc, char **argv, char **env)
{
	t_op	*o;
	t_file	*file;
	int 	i;

	i = 0;
	o = init(o, env);
	o = options(argv, o);
	file = NULL;
	while (argv[++i])
	{
		//if (ft_strcmp(argv[1], "-") != 0)
		file = get_directories(argv[i], file, o);
		//if (o->R)
		//	file = get_sub(file, o);
	}
	file = o->begin;
	while (file)
	{
		printf("%s\n", file->name);
		file = file->next;
	}
	return (0);
}