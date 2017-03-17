/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:34 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/23 03:52:39 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ls.h"

void		error(int error)
{
	if (error == USAGE)
		ft_putendl("Usage: ./ft_ls [invalid argument]");
	if (error == OPTION)
		ft_putendl("ls: illegal option --");
	if (error == ARGUMENT)
		ft_putendl("No such file or directory");
	if (error == ERROR)
		ft_putendl("error");
	else if (error == MALLOC_ERROR)
		ft_putendl("Malloc error");
}


/*
a tester :
ls /etc ; ls -l /etc
ls -l /dev;
ls 9 8 7 5 4 4 4 5 662123 4 6 2;
ls 9 5 4 8 7 1 3 + plusieurs fichier
ls plusieurs fichiers 8 4 2 34 6 4
mkdir testdir; chmod 000 testdir; ls -l testdir
ls -lat -> ou se trouve "." et ".." ? Pourquoi?
ls -lratR -> comprenez vous la raison de l'ordre de chaque lignes?
- permission denied - essaye de lire un fichier sans avoir les droits d'acces
- No such file or directory - si le dossier/fichier n'existe pas
- cd /dev etre sur que le ls peut s'effectuer correctement dans n'importe quelle circonstances (majeurs/mineurs des devices dans /dev)

ls: illegal option -- z
usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]
			ft_putstr("ls: illegal option -- ");
			ft_putchar(argv[i]);
			ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
*/
