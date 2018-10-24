/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:30:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 14:16:34 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_build_tree(t_shell *sh, t_env *env, t_bin *bin, char *cmd)
{
	t_lexer			lexer;
	t_token_tree	*list;

	(void)sh;
	(void)env;
	(void)bin;
	if (!cmd)
		return ;
	lexer = lexer_entry(cmd);
	list = build_list(lexer);
	lexer_delete(&lexer);
	if (!(list = build_token_tree(list))) // IDEA: error message could be nice.
		return ;

	clean_tree(list);
}
