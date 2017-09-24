/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_attr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 01:37:47 by tbouline          #+#    #+#             */
/*   Updated: 2017/09/15 15:48:12 by tbouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void				print_attributes_acl(t_file *file)
{
	acl_t			acl;
	acl_entry_t		entry_p;
	char			*fullpath;

	fullpath = ft_strjoin(file->path, file->name);
	acl = acl_get_link_np(fullpath, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry_p) == -1)
	{
		free(acl);
		acl = NULL;
	}
	else if (acl != NULL)
		ft_putchar('+');
	if ((file->link == 0 && listxattr(fullpath, NULL, 0, 0) > 0) \
		|| (file->link && listxattr(fullpath, NULL, 0, XATTR_NOFOLLOW) > 0))
	{
		ft_putchar('@');
		free(fullpath);
	}
	else
		return ;
}
