/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 00:34:06 by tbouline          #+#    #+#             */
/*   Updated: 2016/11/23 01:10:22 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if (lst)
	{
		new = (t_list *)malloc(sizeof(f(lst)));
		if (new == NULL)
			return (NULL);
		new = f(lst);
		new->next = ft_lstmap(lst->next, f);
		return (new);
	}
	else
		return (NULL);
}
