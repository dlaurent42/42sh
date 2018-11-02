/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 22:27:46 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 18:09:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_command_run_tree(t_shell *sh, t_env *env, t_bin *bin, t_lexer lexer)
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
	if (sh == g_sh &&
	(env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size))
		env_insert_protected(sh, sh->env, "?", status);
	ft_strdel(&status);
	clean_tree(list);
	sh_destroy_exec(&(sh->exec));
	return (STATUS_OK);
}
