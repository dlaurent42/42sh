/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 11:59:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_close_all(t_shell *sh)
{
	t_heredocs	*tmp;

	if (!(tmp = sh->heredocs))
		return ;
	while (tmp->closed)
		tmp = tmp->next;
	if (sh->buffer.ushift + ft_strlens(tmp->keyword) >= ARG_MAX)
		return ;
	ft_strcpy(sh->buffer.content + sh->buffer.ushift, tmp->keyword);
	sh->buffer.unicode_len = ft_strlens(tmp->keyword);
	sh->buffer.display_len = ft_strlenu(tmp->keyword);
	ft_bzero(sh->read->line, LINE_SIZE);
	sh->read->line[0] = '\n';
}

void		sh_read(t_shell *sh)
{
	sh_print_prompt(sh);
	while (TRUE)
	{
		if (read(0, sh->read->line, LINE_SIZE - 1) == -1)
			break ;
		if (sh->read->line[0] == 4 && !sh->modes.multiline
		&& sh->buffer.display_len + sh->buffer.dshift)
			sh_delete_current_char(sh);
		else if (sh->read->line[0] == 4
		&& !sh->modes.multiline && !sh->modes.heredoc)
			break ;
		else if (sh->read->line[0] == 4
		&& sh->modes.heredoc && !sh->buffer.display_len)
			sh_close_all(sh);
		sh_read_dispatcher(sh);
		ft_bzero(sh->read->line, LINE_SIZE);
	}
}
