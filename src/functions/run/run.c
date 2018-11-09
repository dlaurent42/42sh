/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 23:10:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if (lexer.size == 0 && env_search(env, "?"))
		return (ft_atoi(env_search(env, "?")));
	else if (lexer.size == 0)
		return (STATUS_OK);
	sh->modes.multiline = FALSE;
	if (sh && bin == sh->bin)
	{
		sh->bin = bin_update(sh, env, bin);
		bin = sh->bin;
	}
	if (sh == g_sh && !sh->modes.exec && !sh->modes.heredoc
	&& (sh->modes.exec = TRUE))
		command_add(sh, true);
	status = sh_command_run_tree(sh, env, bin, lexer);
	return (lexer_delete(&lexer, status));
}
