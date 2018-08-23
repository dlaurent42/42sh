/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:55:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/04 14:22:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	if (!(lst = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	lst->content = NULL;
	lst->content_size = 0;
	lst->next = NULL;
	if (content != NULL)
	{
		if (!(lst->content = ft_memalloc(content_size)))
			return (lst);
		if (!(lst->content = ft_memcpy(lst->content, content, content_size)))
			return (lst);
		lst->content_size = content_size;
	}
	return (lst);
}
