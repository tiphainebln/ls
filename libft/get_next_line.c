/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 01:28:28 by tbouline          #+#    #+#             */
/*   Updated: 2017/01/05 10:20:37 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int						line_length(char *pos)
{
	int		k;

	k = 0;
	if (pos)
	{
		while (pos[k])
		{
			if (pos[k] == '\n')
				return (k);
			k++;
		}
	}
	return (k);
}

static void						ft_strjoin_custom(char **pos, char *buf)
{
	char		*ret;

	ret = ft_strjoin(*pos, buf);
	free(*pos);
	*pos = NULL;
	*pos = ft_strdup(ret);
	free(ret);
	ret = NULL;
}

static t_gnl					*init_gnl(t_gnl *gnl)
{
	if (gnl == NULL)
	{
		gnl = (t_gnl *)malloc(sizeof(t_gnl));
		gnl->i = 0;
		gnl->pos = ft_strnew(1);
		ft_bzero(&gnl->buf, BUFF_SIZE);
		gnl->ret = 0;
	}
	return (gnl);
}

static t_gnl					*gnl_free(t_gnl *gnl)
{
	if (gnl)
	{
		if (gnl->pos)
		{
			free(gnl->pos);
			gnl->pos = NULL;
		}
		gnl->i = 0;
		free(gnl);
		gnl = NULL;
	}
	return (gnl);
}

int								get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl = NULL;

	gnl = init_gnl(gnl);
	if (fd < 0 || fd > 255)
		return (-1);
	while (((gnl->ret = read(fd, gnl->buf, BUFF_SIZE)) > 0))
	{
		gnl->buf[gnl->ret] = '\0';
		if (gnl->pos)
			ft_strjoin_custom(&gnl->pos, gnl->buf);
		else
			gnl->pos = ft_strdup(gnl->buf);
		if (ft_strchr(gnl->buf, '\n') != NULL)
			break ;
	}
	if (gnl->ret < 0)
		return (-1);
	*line = ft_strsub(gnl->pos, gnl->i, line_length(&(gnl->pos[gnl->i])));
	while (gnl->pos[gnl->i] && gnl->pos[gnl->i] != '\n')
		gnl->i++;
	(gnl->pos[gnl->i] == '\n') ? gnl->i++ : gnl->ret--;
	if (gnl->ret >= 0 || **line != '\0')
		return (1);
	gnl = gnl_free(gnl);
	return (0);
}
