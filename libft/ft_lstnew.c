/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 19:32:18 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/23 02:21:10 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list			*new;
	unsigned char	*t_content;

	t_content = (unsigned char *)malloc(sizeof(unsigned char) * content_size);
	if (!t_content)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
		return (new);
	}
	else
	{
		new->content = ft_memcpy(t_content, content, content_size);
		new->content_size = content_size;
		new->next = NULL;
	}
	return (new);
}
