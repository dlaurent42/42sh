/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:30:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 16:45:49 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_build_tree(t_shell *sh, char *cmd)
{
	t_lexer			lexer;
	t_token_tree	*list;

	if (!cmd)
		return ;
	lexer = lexer_entry(cmd);
	list = build_list(lexer);
	lexer_delete(&lexer);
	if (!(list = build_token_tree(list))) // IDEA: error message could be nice.
		return ;
	// TODO: Reorganise tree(prioritising)
	execute_tree(sh, list); // returns last return code
	clean_tree(list);
}
