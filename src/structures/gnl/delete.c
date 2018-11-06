/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:24:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:28:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	gnl_delete(t_shell *sh)
{
	t_gnl	*tmp;

	tmp = NULL;
	if (!sh->gnl)
		return ;
	sh->gnl = sh->gnl->head;
	while (sh->gnl)
	{
		tmp = sh->gnl->next;
		ft_strdel(&sh->gnl->buff);
		ft_strdel(&sh->gnl->content);
		free(sh->gnl);
		sh->gnl = tmp;
	}
	sh->gnl = NULL;
}
