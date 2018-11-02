/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:30:02 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/31 20:44:46 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*backtick_prep(t_shell *sh, t_env *env, t_bin *bin, char *token)
{
	char		*ret;
	char		status;
	t_lexer		lexer;

	if (sh->env == env && !sh->modes.heredoc)
		token = sh_replace_aliases(sh->alias, token);
	if ((status = sh_command_run_lexer(sh, env, &lexer, &token)) != STATUS_OK)
	{
		lexer_delete(&lexer, status);
		return (ft_strdups(""));
	}
	if ((status = sh_command_check_lexer(sh, &lexer)) != STATUS_OK)
	{
		lexer_delete(&lexer, status);
		return (ft_strdups(""));
	}
	if (lexer.size == 0)
		return (ft_strdups(""));
	ret = execute_backtick(sh, env, bin, lexer);
	lexer_delete(&lexer, status);
	return (ret);
}
