/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 22:29:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 13:29:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_command_run_lexer(
		t_shell *sh, t_env *env, t_lexer *lexer, char **cmd)
{
	char	status;

	(void)env;
	ft_bzero((void *)lexer, sizeof(t_lexer));
	if ((status = brackets(*cmd, '\0')) != STATUS_OK)
		return (status == STATUS_ERR ? parse_error("\\n") : status);
	if (sh->modes.heredoc == FALSE && lexer_is_empty(*cmd))
		return (STATUS_EMPTY);
	else if (sh_heredocs_all_close(sh))
		status = lexer_fill(lexer, *cmd);
	else
	{
		if ((status = sh_heredoc(sh, NULL)) == STATUS_OK)
		{
			cmd = &sh->buffer.parsed;
			status = lexer_fill(lexer, *cmd);
		}
	}
	return (status == STATUS_ERR ? parse_error("\\n") : status);
}
