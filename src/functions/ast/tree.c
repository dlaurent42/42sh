/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:30:34 by azaliaus          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/10/26 20:55:32 by azaliaus         ###   ########.fr       */
=======
/*   Updated: 2018/10/26 22:55:03 by azaliaus         ###   ########.fr       */
>>>>>>> 314b09aefe9ce8fff4d89343fd2ffa8d58184d60
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_build_tree(t_shell *sh, char *cmd)
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
	if ((list = build_token_tree(list)))
	{
		// printf("Node: %s\n", list->tokens[0]);
		// printf("Prev node left: %s\n", list->left->tokens[0]);
		// printf("Prev node right: %s\n", list->right->tokens[0]);
		// printf("Prev node left right: %s\n", list->left->right->tokens[0]);
		return (0); // tmp
		ret = execute_tree(sh, list);
	}
	else
		ret = error_execution_tree();
	clean_tree(list);
	return (ret);
}
