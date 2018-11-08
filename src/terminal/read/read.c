/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/08 16:24:20 by dlaurent         ###   ########.fr       */
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

static bool	sh_read_stop(t_shell *sh)
{
	if (sh->read->line[0] != 4)
		return (FALSE);
	if (sh->modes.heredoc && !sh->buffer.display_len)
		sh_close_all(sh);
	else if (sh->buffer.display_len + sh->buffer.dshift)
		sh_delete_current_char(sh);
	else if (sh->job)
	{
		ft_putstr_fd("\nsh: you have suspended jobs.", 2);
		sh_sigint_reset(sh, "0");
	}
	else if (!sh->modes.multiline)
		return (TRUE);
	return (FALSE);
}

char		sh_read(t_shell *sh)
{
	(!sh->modes.subshell) ? sh_print_prompt(sh) : 0;
	while ((!sh->modes.subshell && TRUE) || sh->modes.subshell == 1)
	{
		if (((sh->modes.subshell && sh->modes.multiline)
		|| !sh->modes.subshell))
			if (read(0, sh->read->line, LINE_SIZE - 1) == -1)
				break ;
		if (sh_read_stop(sh))
			break ;
		sh_read_dispatcher(sh);
		ft_bzero(sh->read->line, LINE_SIZE);
	}
	return (EXIT_SUCCESS);
}
