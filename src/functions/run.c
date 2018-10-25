/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 15:37:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_run_checks(t_shell *sh, t_env *env, char **cmd)
{
	ft_printf(". Enters command checks\n");
	if (!*cmd || lexer_is_empty(*cmd))
	{
		ft_printf(". Exits command checks (STATUS EMPTY)\n");
		return (STATUS_EMPTY);
	}
	*cmd = (sh->env == env)
		? sh_command_check(env, sh->alias, *cmd)
		: sh_command_check(env, NULL, *cmd);
	ft_printf(". Exits command checks (STATUS OK)\n");
	return (STATUS_OK);
}

static char	sh_command_run_lexer(
	t_shell *sh, t_env *env, t_lexer *lexer, char *cmd)
{
	char	status;

	(void)env;
	ft_bzero((void *)lexer, sizeof(t_lexer));
	status = (sh->modes.heredoc == FALSE)
		? lexer_fill(lexer, cmd)
		: sh_heredoc(sh, NULL);
	return (status);
}

// static char	sh_command_run_ast(
// 	t_shell *sh, t_env *env, t_bin *bin, t_lexer lexer)
// {
// 	char			status;
// 	t_token_tree	*list;

// 	list = build_list(lexer);
// 	lexer_delete(&lexer, status);
// 	if ((list = build_token_tree(list)))
// 	{
// 		// TODO: Reorganise tree(prioritising)
// 		status = execute_tree(sh, list); // returns last return code
// 	}
// 	else
// 		status = error_execution_tree();
// 	clean_tree(list);
// 	return (status);
// }

char		sh_command_run(t_shell *sh, t_env *env, t_bin *bin, char **cmd)
{
	char			status;
	t_lexer			lexer;

	status = STATUS_OK;
	ft_printf("Enters command run %s\n", *cmd);
	if ((status = sh_command_run_checks(sh, env, cmd)) != STATUS_OK)
	{
		ft_printf("Exit command run (1: wrong status = %d)\n", status);
		return (status);
	}
	ft_printf("Command checks are now over %s\n", *cmd);
	if ((status = sh_command_run_lexer(sh, env, &lexer, *cmd)) != STATUS_OK)
	{
		ft_printf("Exit command run (1: wrong status = %d)\n", status);
		return (lexer_delete(&lexer, status));
	}
	sh->modes.multiline = FALSE;
	if ((sh->modes.exec = TRUE) && bin == sh->bin)
	{
		ft_printf("Updating sh->bin\n");
		sh->bin = bin_update(sh, env, bin);
		command_add(sh, true);
	}
	ft_printf("Exit command run\n");
//	status = sh_command_run_ast(sh, env, bin, lexer);
	return (lexer_delete(&lexer, status));
}
