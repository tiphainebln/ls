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
# define PERMISSION 6
# define NOTHINGTODO 0

# define NAME 0
# define TIME 1
# define REVNAME 2
# define PATH 3
# define REVPATH 4
# define ENTRY 5
# define REVENTRY 6

typedef struct 			s_file
{
	int 				completed;
	char				*name;
	off_t				st_size;
	char				*path;
	unsigned char		type;
	nlink_t				st_nlink;
	mode_t				st_mode;
	gid_t				st_gid;
	uid_t				st_uid;
	blkcnt_t			st_blocks;
	blksize_t			st_blksize;
	time_t				st_mtimes;
	struct s_file		*next;
	char 				*grp;
	char 				*uid;
	int 				visited;
	int 				relative;
	int 				file;
	int 				noarg;
	int 				minor;
	int 				major;
	char 				*linkname;
	char 				*displayname;
	char 				*error;
	int 				typereal;
	int 				first;
	char 				*nameasadir;
	char 				*entry;
	int 				file_error;
	int 				sub;
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
	size_t 				nbgrpspace;
	size_t 				nbuidspace;
	int 				nbminorspace;
	int 				nbmajorspace;
	int 				noarg;
	int 				relative;
	int 				args;
	int 				link;
	char 				*linkname;
	char				*error;
	t_file				*latest;
	char 				*entry;
	int 				sub;
	char 				**order;
	int 				error_happened;
}						t_op;

t_file					*add_error(char *name, t_op *op);
void					print_major_minor(t_file *file, t_op *op);
void					init_tab(int (*tab[13])(void));
void					manage_error(t_file *file, int error, t_op *op, char *entry);
t_op					*init(t_op *op, char **env);
t_op					*options(char **argv, t_op *o);
char					*get_fname(char *entry);
t_file					*print_fname(t_file *file, char *entry);
void					change_dir(char **old, char *new, int free_needed);
t_op 					*get_options(char *argv, t_op *o);
t_file					*get_directory(char *argv, t_file *file, t_op *op, int sub);
t_file					*read_content(t_file *file, DIR *ret, t_op *op);
t_file					*new_list(t_file *file, struct dirent *dirent, t_op *op);
t_file					*store_basic(t_file *file, struct stat data);
t_file					*store_groups_uid(t_file *file);
t_file					*nb_spaces(t_file *file, t_op *op);
t_file					*get_sub(t_file *file, t_op *op, int where);
int 					only_contains_hidden(t_file *start);
int 					ft_checkhiddendir(char *str);
t_file					*print_grp(t_file *file, t_op *op);
t_file					*print_uid(t_file *file, t_op *op);
void 					file_type_letter(t_file *file);
int						print_rights(t_file *file, t_op *op);
t_file					*print_total(t_file *file, t_op *op);
t_file					*print_size(t_file *file, t_op *op);
t_file					*print_links(t_file *file);
t_file					*long_format(t_file *file, t_op *op, int (*tab[13])(void));
t_file					*add_file(struct stat data, t_op *op, char *entry);
t_file					*new_file(t_file *file, t_op *op, char *entry);
int 					opt_a(t_file *file, t_op *op, char **argv);
void					ft_putspaces(t_file *file, t_op *op, int choice);
t_file					*print_time(t_file *file);
int						determine_type(struct stat data);
char					*store_path(char *entry, t_op *op);
void					write_path(char *path, char *origin, int noarg, int relative);
int 					same_path_everywhere(t_file *file);
void					read_link(char *path);
void					check_rights(t_file *file);
t_file					*sort(t_file *file, int tri);
int						ft_second_to_last(char *str);
int						ft_isitover(t_file *file);
t_file					*store_lnk(t_file *file, t_op *op, struct stat data);
t_file					*visited_or_completed(t_file *file);
t_op 					*data_op(t_op *op);
t_file					*display_path(t_file *file, t_op *op, char **argv, int (*tab[13])(void));
struct stat				read_links(t_file *file, t_op *op, char *fullpath);
int						ft_putblk(void);
int 					ft_putchr(void);
int 					ft_putdir(void);
int						ft_putfifo(void);
int 					ft_putlnk(void);
int 					ft_putreg(void);
int						ft_putsoc(void);
int 					ft_putwat(void);
#endif
