/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 22:29:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 14:11:40 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_command_run_lexer(
		t_shell *sh, t_env *env, t_lexer *lexer, char **cmd)
{
	char	status;

	(void)env;
	ft_bzero((void *)lexer, sizeof(t_lexer));
	if (sh->modes.heredoc == FALSE && lexer_is_empty(*cmd))
		return (STATUS_EMPTY);
	if ((status = brackets(*cmd, '\0')) != STATUS_OK)
		;
	else if (sh_heredocs_all_close(sh))
		status = lexer_fill(lexer, *cmd);
	else
	{
		if ((status = sh_heredoc(sh, NULL)) == STATUS_OK)
		{
			*cmd = sh->buffer.parsed;
			status = lexer_fill(lexer, *cmd);
		}
	}
	return (status);
}

static bool	is_operator(t_token_type type)
{
	return (type >= TOKEN_ANDIF && type <= TOKEN_HEREDOC);
}

char		sh_command_check_lexer(t_shell *sh, t_lexer *lexer)
{
	int		i;
	char	status;
	t_token	token;

	i = -1;
	status = STATUS_OK;
	while (++i < (int)lexer->size)
	{
		token = lexer->tokens[i];
		if ((i + 1) >= (int)lexer->size && token.type == TOKEN_PIPE)
			return (STATUS_PIPE);
		else if ((i + 1) >= (int)lexer->size && is_operator(token.type))
			return (STATUS_ERR);
		if (is_operator(token.type) && (i == 0
					|| lexer->tokens[i + 1].type == TOKEN_SEMICOLON
					|| is_operator(lexer->tokens[i + 1].type)))
			return (STATUS_ERR);
		if (token.type == TOKEN_AGGREG
				&& lexer_token_merge(lexer, i) != STATUS_OK)
			return (STATUS_ERR);
		if (lexer->tokens[i].type == TOKEN_HEREDOC)
			if ((status = sh_heredoc(sh, lexer->tokens[i + 1].id)) == -1)
				return (status);
	}
	return (status);
}
