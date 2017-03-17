/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:53:11 by tbouline          #+#    #+#             */
/*   Updated: 2017/02/23 03:53:13 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include "libft/libft.h"

# define USAGE 1
# define OPTION 2
# define ARGUMENT 3
# define ERROR 4
# define MALLOC_ERROR 5

typedef struct 			s_file
{
	int 				visited;
	int 				completed;
	char				*name;
	off_t				st_size;
	char				*path;
	char				*directory;
	unsigned char		type;
	nlink_t				st_nlink;
	mode_t				st_mode;
	gid_t				st_gid;
	uid_t				st_uid;
	blkcnt_t			st_blocks;
	blksize_t			st_blksize;
	char				*id;
	char				*grp;
	struct s_file		*next;
}						t_file;

typedef struct 			s_op
{
	unsigned int		a;
	unsigned int		t;
	unsigned int		r;
	unsigned int		R;
	unsigned int		l;
	t_file				*begin;
	char				*origin;
	char				*current;
}						t_op;

typedef struct 			s_ls
{

}						t_ls;

void					error(int error);
t_op					*init(t_op *op, char **env);
t_op					*options(char **argv, t_op *o);
t_op 					*get_options(char *argv, t_op *o);
t_file					*print_fname(t_file *file, t_op *op, char *content);
t_file					*get_directories(char *argv, t_file *file, t_op *op);
t_file					*read_content(t_file *file, DIR *ret, t_op *op);
t_file					*new_list(t_file *file, t_op *op);
t_file					*get_sub(t_file *file, t_op *op);
t_file					*print_grp(t_file *file);
t_file					*print_uid(t_file *file);
int 					file_type_letter(t_file *file);
int						print_rights(t_file *file);
t_file					*print_total(t_file *file, t_op *op);
t_file					*print_size(t_file *file, t_op *op);
t_file					*print_links(t_file *file, t_op *op);
t_file					*long_format(t_file *file, t_op *op);

#endif
