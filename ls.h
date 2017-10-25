/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:53:11 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/25 21:55:14 by tbouline         ###   ########.fr       */
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
# include <sys/xattr.h>
# include <sys/acl.h>

# define USAGE 1
# define OPTION 2
# define ARGUMENT 3
# define ERROR 4
# define PERMISSION 5
# define NOTHINGTODO 0

# define NAME 1
# define REVNAME 2
# define PATH 3
# define REVPATH 4
# define PATHTIME 5
# define REVPATHTIME 6
# define TIME 7
# define REVTIME 8
# define ROOTTIME 9

typedef struct		s_file
{
	int 			index;
	int 			highestsub;
	int				completed;
	char			*name;
	off_t			st_size;
	char			*path;
	unsigned char	type;
	nlink_t			st_nlink;
	mode_t			st_mode;
	gid_t			st_gid;
	uid_t			st_uid;
	blkcnt_t		st_blocks;
	blksize_t		st_blksize;
	time_t			st_mtimes;
	long 			st_mntimes;
	time_t			foldertime;
	long 			microfoldertime;
	struct s_file	*next;
	char			*grp;
	char			*uid;
	int				visited;
	int				relative;
	int				file;
	int				noarg;
	int				minor;
	int				major;
	char			*linkname;
	char			*displayname;
	char			*error;
	int				typereal;
	int				first;
	char			*nameasadir;
	char			*entry;
	int				file_error;
	int				sub;
	char			*errorname;
	int				nblinkspace;
	int				nbsizespace;
	size_t			nbgrpspace;
	size_t			nbuidspace;
	int				nbminorspace;
	int				nbmajorspace;
	int				directorytime;
	int				link;
	int				acl;
	int				attr;
	int 			insize;
	int 			nmerges;
	int 			psize;
	int 			qsize;
	int 			rightsize;
}					t_file;

typedef struct		s_op
{
	unsigned int	a;
	unsigned int	t;
	unsigned int	r;
	unsigned int	R;
	unsigned int	l;
	unsigned int	d;
	unsigned int	un;
	unsigned int	G;
	t_file			*begin;
	char			*origin;
	char			*current;
	int				nblinkspace;
	int				nbsizespace;
	size_t			nbgrpspace;
	size_t			nbuidspace;
	int				nbminorspace;
	int				nbmajorspace;
	int				noarg;
	int				relative;
	int				args;
	int				link;
	char			*linkname;
	char			*error;
	t_file			*latest;
	char			*entry;
	int				sub;
	char			**order;
	int				error_happened;
	char			**epured;
	int				doubledash;
	int				error_epur;
	int				theresbeenamistake;
	int 			option;
	int 			rightsize;
}					t_op;

char				**ft_sort_ascii_string(char **av, t_op *op);
char				**ft_sort_time(char **av, t_op *op);
char				**sort_entry(char **entries, t_op *op);
char				**sort_t_entry(char **entries, t_op *op);
char				*father(char *current);
char				*get_fname(char *entry);
char				*store_path(char *entry, t_op *op);
int					cmp_list(t_file *a, t_file *b, int tri);
int					determine_type(struct stat data);
int					does_it_exist(char *argv, t_op *op, t_file *file);
int					ft_checkhiddendir(char *str);
int					ft_isitover(t_file *file);
int					ft_issort(char **av, t_op *op);
int					ft_putblk(void);
int					ft_putchr(void);
int					ft_putdir(void);
int					ft_putfifo(void);
int					ft_putlnk(void);
int					ft_putreg(void);
int					ft_putsoc(void);
int					ft_putwat(void);
int					ft_second_to_last(char *str);
int					only_contains_hidden(t_file *start);
int					opt_a(t_file *file, t_op *op, char **argv);
int					print_rights(t_file *file);
int					same_path_everywhere(t_file *file);
int					strfils(char *patha, char *pathb);
int					everything_is_empty(t_file *file);
int					is_option(char *av, t_op *op);
struct stat			get_stat(char *av, t_op *op);
struct stat			read_links(t_file *f, t_op *op, char *fp, int v);
t_file				*add_error(char *name, t_op *op);
t_file				*add_file(struct stat data, t_op *op, char *entry);
t_file				*aff_path(t_file *f, t_op *op, char **a, int (*tab[13])());
t_file				*display_regular(t_file *file, t_op *op, int (*tab[13])());
t_file				*empty_directory(t_file *file, char *oldpath, t_op *op);
t_file				*get_directory(char *av, t_file *f, t_op *op, int sub);
t_file				*get_sub(t_file *f, t_op *op, int w, t_file *cd);
t_file				*inject_time(t_file *file, t_op *op);
t_file				*new_file(t_file *file, t_op *op, char *entry);
t_file				*new_file(t_file *file, t_op *op, char *entry);
t_file				*new_list(t_file *file, struct dirent *drt, t_op *op);
t_file				*print_fname(t_file *file, char *entry);
t_file				*print_grp(t_file *file);
t_file				*print_links(t_file *file);
t_file				*print_size(t_file *file);
t_file				*print_time(t_file *file);
t_file				*print_total(t_file *file, t_op *op);
t_file				*print_uid(t_file *file);
t_file				*read_content(t_file *file, DIR *ret, t_op *op);
t_file				*sort(t_file *file, int tri);
t_file				*sort_lst(t_file *file, t_op *op);
t_file				*space_central(t_file *file, t_op *op);
t_file				*store_basic(t_file *file, struct stat data);
t_file				*store_groups_uid(t_file *file);
t_file				*store_lnk(t_file *file, t_op *op, struct stat data);
t_file				*store_space(t_file *file, t_op *op);
t_file				*visited_or_completed(t_file *file);
t_op				*data_op(t_op *op);
t_op				*epur_and_sort(char **argv, t_op *op, t_file *file);
t_op				*get_options(char *argv, t_op *o);
t_op				*init(t_op *op, char **env);
t_op				*init_space(t_op *op);
t_op				*nb_spaces(t_file *file, t_op *op);
t_op				*options(char **argv, t_op *o, t_file *file);
int					write_path(char *path, char *orgn, int noarg, int rltv);
time_t				get_time(char *path, char *name, t_op *op);
void				change_dir(char **old, char *new, int free_needed);
void				check_rights(t_file *file);
void				ft_putspaces(t_file *file, int choice);
void				init_tab(int (*tab[13])(void));
void				manage_error(t_file *f, int error, t_op *op, char *av);
t_file				*print_attributes_acl(t_file *file);
void				print_major_minor(t_file *file);
void				print_type_letter(t_file *file);
void				read_link(char *path);

#endif
