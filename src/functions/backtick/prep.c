/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:30:02 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 15:41:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*backtick_prep(t_shell *sh, t_env *env, char *token)
{
	char		*ret;
	char		status;
	t_lexer		lexer;

	if (sh->env == env && !sh->modes.heredoc)
		token = sh_replace_aliases(sh->alias, token);
	if ((status = sh_command_run_lexer(sh, env, &lexer, &token)) != STATUS_OK)
	{
		ft_strdel(&token);
		lexer_delete(&lexer, status);
		return (ft_strdups(""));
	}
	ft_strdel(&token);
	if ((status = sh_command_check_lexer(sh, &lexer)) != STATUS_OK)
	{
		lexer_delete(&lexer, status);
		return (ft_strdups(""));
	}
	if (lexer.size == 0)
		return (ft_strdups(""));
	if (!(ret = execute_backtick(sh, lexer)))
		ret = ft_strdups("");
	lexer_delete(&lexer, status);
	return (ret);
}
