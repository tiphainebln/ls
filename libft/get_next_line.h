/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 00:54:15 by tbouline          #+#    #+#             */
/*   Updated: 2017/01/16 03:59:38 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 32

typedef struct		s_gnl
{
	char			buf[BUFF_SIZE + 1];
	char			*pos;
	int				i;
	int				ret;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
