/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:30:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 17:53:21 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static char	error_init_exec(t_shell *sh)
{
	(sh) ? sh_delete(sh) : 0;
	ft_putstr_fd("Cannot malloc exec", 2);
	exit(EXIT_FAILURE);
	return (1);
}

char		sh_build_tree(t_shell *sh, t_env *env, t_bin *bin, char *cmd)
{
	char			ret;
	t_lexer			lexer;
	t_token_tree	*list;

	if (!cmd)
		return (1);
	lexer = lexer_entry(cmd);
	list = build_list(lexer);
	lexer_delete(&lexer);
	reorganise_tokens(&list);
	if (!(sh->exec = sh_init_exec(env, bin)))
		return (error_init_exec(sh));
	if ((list = build_token_tree(list)))
		ret = execute_tree(sh, list);
	else
		ret = error_execution_tree();
	clean_tree(list);
	sh_destroy_exec(&(sh->exec));
	return (ret);
}
