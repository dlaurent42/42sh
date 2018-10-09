/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 21:35:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 18:49:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		command_add_str_based(t_shell *sh, char *str, bool is_new)
{
	t_cmd	*new;

	if (!str || !str[0])
		return ;
	if (sh->cmd && ft_strcmps(sh->cmd->content, str) == 0)
		return ;
	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return ;
	new->id = (sh->cmd) ? sh->cmd->id + 1 : 1;
	ft_strcpy(new->content, str);
	new->display_len = ft_strlenu(str);
	new->unicode_len = ft_strlens(str);
	new->is_new = is_new;
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
}

void		command_add(t_shell *sh, bool is_new)
{
	t_cmd	*new;

	if (sh->cmd && ft_strcmps(sh->cmd->content, sh->buffer.content) == 0)
		return ;
	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return ;
	new->id = (sh->cmd) ? sh->cmd->id + 1 : 1;
	ft_strcpy(new->content, sh->buffer.content);
	new->display_len = sh->buffer.display_len + sh->buffer.dshift;
	new->unicode_len = sh->buffer.unicode_len + sh->buffer.ushift;
	new->is_new = is_new;
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
}
