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
		if (argc == 0)
		print_fname(argv[i]);
	while (argv[++i])
	{
		if (argv[i][0] != '-')
			file = get_directory(argv[i], file, o);
		//if (o->R)
		//	file = get_sub(file, o);
	}
	file = o->begin;
	long_format(file, o);
	/*
	while (file)
	{
		ft_putstr(file->name);
		ft_putchar('\n');
		file = file->next;
	}
	
	
	print_total(file, o);
	while (file)
	{
		if (opt_a(file, o) == 0)
		{
			file = file->next;
			continue ;
		}
		if (file->type == DT_DIR)
			ft_putstr("\033[31m");
		file_type_letter(file);
		print_rights(file, o);
		print_links(file, o);
		print_uid(file, o);
		print_grp(file, o);
		print_size(file, o);
		print_time(file);
		ft_putstr(file->name);
		ft_putchar('\n');
		file = file->next;
		ft_putstr("\033[00m");
	}
	*/
	return (0);
}