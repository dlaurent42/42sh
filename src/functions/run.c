/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 15:52:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_run_lexer(
	t_shell *sh, t_env *env, t_lexer *lexer, char *cmd)
{
	char	status;

	(void)env;
	ft_bzero((void *)lexer, sizeof(t_lexer));
	if (sh->modes.heredoc == FALSE && lexer_is_empty((char *)cmd))
		return (STATUS_ERR);
	status = (sh->modes.heredoc == FALSE)
		? lexer_fill(lexer, cmd)
		: sh_heredoc(sh, NULL);
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
	ft_printf("env search is %s (sh_command_run_tree)\n", env_search(sh->env, "?"));
	ft_strdel(&status);
	clean_tree(list);
	sh_destroy_exec(&(sh->exec));
	return (STATUS_OK);
}

static char	sh_command_check_lexer(t_shell *sh, t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < lexer->size)
	{
		if (i == 0 && lexer->tokens[i].type < 6 && lexer->tokens[i].type != TOKEN_SEMICOLON)
			return (STATUS_ERR);
		if (lexer->tokens[i].type == TOKEN_PIPE && (i + 1) >= lexer->size)
			return (STATUS_PIPE);
		if ((lexer->tokens[i].type == TOKEN_AGGREG || lexer->tokens[i].type == TOKEN_MERGE)
			&& lexer_token_merge(lexer, i) != STATUS_OK)
			return (STATUS_ERR);
		if (lexer->tokens[i].type == TOKEN_HEREDOC)
		{
			if ((i + 1) >= lexer->size)
				return (STATUS_ERR);
			sh_heredoc(sh, lexer->tokens[i + 1].id);
			return (STATUS_HEREDOC);
		}
		++i;
	}
	return (STATUS_OK);
}

char		sh_command_run(t_shell *sh, t_env *env, t_bin *bin, char **cmd)
{
	(void)bin;
	char			status;
	t_lexer			lexer;

	status = STATUS_OK;
	ft_printf("Enters command run %s\n", *cmd);
	*cmd = (sh->env == env) ? sh_replace_aliases(sh->alias, *cmd) : 0;
	ft_printf("Command checks are now over %s\n", *cmd);
	if ((status = sh_command_run_lexer(sh, env, &lexer, *cmd)) != STATUS_OK)
	{
		ft_printf("Exit command run (1: wrong status = %d)\n", status);
		return (lexer_delete(&lexer, status));
	}
	if ((status = sh_command_check_lexer(sh, &lexer)) != STATUS_OK)
	{
		ft_printf("Exit command run (1: wrong status = %d)\n", status);
		return (lexer_delete(&lexer, status));
	}
	sh->modes.multiline = FALSE;
	if (sh && bin == sh->bin)
	{
		ft_printf("Updating sh->bin\n");
		sh->bin = bin_update(sh, env, bin);
		bin = sh->bin;
		ft_printf("Updated sh->bin\n");
	}
	(sh->modes.exec)
		? ft_printf("Exec mode is On\n")
		: ft_printf("Exec mode is Off\n");
	if (!sh->modes.exec && (sh->modes.exec = TRUE))
	{
		ft_printf("Adding command to hist\n");
		command_add(sh, true);
		ft_printf("Added command to hist\n");
	}
	status = sh_command_run_tree(sh, env, bin, lexer);
	ft_printf("env search is %s (sh_command_run)\n", env_search(sh->env, "?"));
	ft_printf("tree has finished with status %d\n", status);

	ft_printf("Exit command run with status %d\n", status);
	return (lexer_delete(&lexer, status));
}
