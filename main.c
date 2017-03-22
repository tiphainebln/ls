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
		if (argv[i][0] != '-')
			file = get_directory(argv[i], file, o);
		//if (o->R)
		//	file = get_sub(file, o);
	}
	file = o->begin;
	print_total(file, o);
	while (file)
	{
		if (opt_a(file, o) == 0)
		{
			file = file->next;
			continue ;
		}
		if (file->type == DT_DIR)
			ft_putstr("\033[34m");
		print_grp(file);
		print_uid(file);
		file_type_letter(file);
		print_rights(file);
		print_size(file, o);
		print_links(file, o);
		ft_putstr(file->name);
		ft_putchar('\n');
		file = file->next;
		ft_putstr("\033[00m");
	}
	return (0);
}