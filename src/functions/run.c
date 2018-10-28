/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 20:18:45 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_run_lexer(
	t_shell *sh, t_env *env, t_lexer *lexer, char **cmd)
{
	char	status;

	(void)env;
	ft_bzero((void *)lexer, sizeof(t_lexer));
	if (sh->modes.heredoc == FALSE && lexer_is_empty((char *)cmd))
		return (STATUS_ERR);
	if (sh_heredocs_all_close(sh))
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

static char	sh_command_run_tree(
	t_shell *sh, t_env *env, t_bin *bin, t_lexer lexer)
{
	char			ret;
	char			*status;
	t_token_tree	*list;

	list = build_list(lexer);
	reorganise_tokens(&list);
	if (!(sh->exec = sh_init_exec(env, bin)))
	{
		clean_tree(list);
		return (STATUS_ERR);
	}
	list = build_token_tree(list);
	ret = (list) ? execute_tree(sh, list) : error_execution_tree();
	status = (sh) ? ft_itoa(ret) : ft_strdups("0");
	if ((env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size))
		env_insert_protected(sh, sh->env, "?", status);
	ft_strdel(&status);
	clean_tree(list);
	sh_destroy_exec(&(sh->exec));
	return (STATUS_OK);
}

static char	sh_command_check_lexer(t_shell *sh, t_lexer *lexer)
{
	size_t	i;
	char	status;

	i = 0;
	status = STATUS_OK;
	while (i < lexer->size)
	{
		if (i == 0 && lexer->tokens[i].type < 6
		&& lexer->tokens[i].type != TOKEN_SEMICOLON)
			return (STATUS_ERR);
		if (lexer->tokens[i].type == TOKEN_PIPE && (i + 1) >= lexer->size)
			return (STATUS_PIPE);
		if (lexer->tokens[i].type == TOKEN_AGGREG
		&& lexer_token_merge(lexer, i) != STATUS_OK)
			return (STATUS_ERR);
		if (lexer->tokens[i].type == TOKEN_HEREDOC)
		{
			if ((i + 1) >= lexer->size)
				return (STATUS_ERR);
			if ((status = sh_heredoc(sh, lexer->tokens[i + 1].id)) == -1)
				return (status);
		}
		++i;
	}
	return (status);
}

char		sh_command_run(t_shell *sh, t_env *env, t_bin *bin, char **cmd)
{
	char			status;
	t_lexer			lexer;

	status = STATUS_OK;
	if (sh->env == env && !sh->modes.heredoc)
		*cmd = sh_replace_aliases(sh->alias, *cmd);
	if ((status = sh_command_run_lexer(sh, env, &lexer, cmd)) != STATUS_OK)
		return (lexer_delete(&lexer, status));
	if ((status = sh_command_check_lexer(sh, &lexer)) != STATUS_OK)
		return (lexer_delete(&lexer, status));
	sh->modes.multiline = FALSE;
	if (sh && bin == sh->bin)
	{
		sh->bin = bin_update(sh, env, bin);
		bin = sh->bin;
	}
	if (!sh->modes.exec && (sh->modes.exec = TRUE) && !sh->modes.heredoc)
		command_add(sh, true);
	status = sh_command_run_tree(sh, env, bin, lexer);
	return (lexer_delete(&lexer, status));
}
