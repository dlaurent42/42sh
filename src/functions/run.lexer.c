/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 22:29:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 15:30:08 by dlaurent         ###   ########.fr       */
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
		;
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
	return (status);
}

static bool	is_operator(t_token_type type)
{
	return (type >= TOKEN_ANDIF && type <= TOKEN_HEREDOC);
}

char		sh_command_check_lexer(t_shell *sh, t_lexer *l)
{
	int		i;
	char	status;
	t_token	t;

	i = -1;
	status = STATUS_OK;
	while (++i < (int)l->size)
	{
		t = l->tokens[i];
		if ((i + 1) >= (int)l->size && t.type == TOKEN_PIPE)
			return (STATUS_PIPE);
		else if ((i + 1) >= (int)l->size && is_operator(t.type))
			return (parse_error("\\n"));
		if (is_operator(t.type) && (i == 0
			|| l->tokens[i + 1].type == TOKEN_SEMICOLON
			|| is_operator(l->tokens[i + 1].type)
			|| (i - 1 >= 0 && l->tokens[i - 1].type == TOKEN_SEMICOLON)))
			return (parse_error(l->tokens[i].id));
		if (t.type == TOKEN_AGGREG && lexer_token_merge(l, i) != STATUS_OK)
			return (parse_error("\\n"));
		if (l->tokens[i].type == TOKEN_HEREDOC)
			if ((status = sh_heredoc(sh, l->tokens[i + 1].id)) == -1)
				return (status);
	}
	return (status);
}
