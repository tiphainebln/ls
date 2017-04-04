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
	time_t				mtime;
	char				*id;
	struct s_file		*next;
	char 				*grp;
	char 				*uid;
	int 				visited;
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
	int 				nblinkspace;
	int 				nbsizespace;
	int 				nbgrpspace;
	int 				nbuidspace;
}						t_op;

typedef struct 			s_ls
{

}						t_ls;

void					init_tab(int (*tab[13])(void));
void					error(int error);
t_op					*init(t_op *op, char **env);
t_op					*options(char **argv, t_op *o);
char					*get_fname(char *entry);
t_file					*print_fname(t_file *file, char *entry);
t_op 					*get_options(char *argv, t_op *o);
t_file					*get_directory(char *argv, t_file *file, t_op *op, int sub);
t_file					*read_content(t_file *file, DIR *ret, t_op *op);
t_file					*new_list(t_file *file, struct dirent *dirent, t_op *op);
t_file					*store_basic(t_file *file, struct stat *data, t_op *op);
t_file					*store_groups_uid(t_file *file, t_op *op);
t_file					*get_sub(t_file *file, t_op *op);
t_file					*print_grp(t_file *file, t_op *op);
t_file					*print_uid(t_file *file, t_op *op);
int 					file_type_letter(t_file *file);
int						print_rights(t_file *file, t_op *op);
t_file					*print_total(t_file *file, t_op *op);
t_file					*print_size(t_file *file, t_op *op);
t_file					*print_links(t_file *file, t_op *op);
t_file					*long_format(t_file *file, t_op *op);
t_file					*add_file(struct stat *data, t_op *op, char *entry);
t_file					*new_file(t_file *file, t_op *op, char *entry);
int 					opt_a(t_file *file, t_op *op);
void					ft_putspaces(t_file *file, t_op *op, int choice);
t_file					*print_time(t_file *file);
int						ft_putblk(void);
int 					ft_putchr(void);
int 					ft_putdir(void);
int						ft_putfifo(void);
int 					ft_putlnk(void);
int 					ft_putreg(void);
int						ft_putsoc(void);
int 					ft_putwat(void);
#endif
