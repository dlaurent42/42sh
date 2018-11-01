/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 21:35:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 15:10:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	command_parse_cmd_content(t_shell *sh)
{
	size_t	i;

	i = 0;
	if (!sh->cmd)
		return ;
	while (sh->cmd->content[i])
	{
		if (sh->cmd->content[i] == '\n')
		{
			lexer_repatriate(sh->cmd->content, i, 1);
			sh->cmd->display_len--;
			sh->cmd->unicode_len--;
		}
		else
			i++;
	}
}

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
	ft_strncpy(new->content, str, ARG_MAX);
	new->display_len = ft_strlenu(str);
	new->unicode_len = ft_strlens(str);
	new->is_new = is_new;
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
	command_parse_cmd_content(sh);
}

void		command_add(t_shell *sh, bool is_new)
{
	t_cmd	*new;

	if (sh->cmd && ft_strcmps(sh->cmd->content, sh->buffer.content) == 0)
		return ;
	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return ;
	new->id = (sh->cmd) ? sh->cmd->id + 1 : 1;
	ft_strncpy(new->content, sh->buffer.content, ARG_MAX);
	new->display_len = sh->buffer.display_len + sh->buffer.dshift;
	new->unicode_len = sh->buffer.unicode_len + sh->buffer.ushift;
	new->is_new = is_new;
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
	command_parse_cmd_content(sh);
}
