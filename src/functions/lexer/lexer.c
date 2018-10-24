/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 18:20:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** sh_command_lexer will be deleted and replaced by Adam file
*/

char		sh_command_lexer(t_shell *sh, t_env *env, char *str)
{
	char			status;
	t_lexer			lexer;

	status = 0;
	ft_bzero((void *)&lexer, sizeof(t_lexer));
	status = (sh->modes.heredoc == FALSE)
		? lexer_fill((&lexer, str)
		: sh_heredoc(sh, NULL);
	if (status != 0)
		return (lexer_delete(&lexer, status));
	command_add(sh, true);
	/*
	Adam stuff
	*/
	return (status);
}


/*
** Function from Adam
**
** void		sh_build_tree(t_shell *sh, t_env *env, t_bin *bin, char *cmd)
** {
** 	t_lexer			lexer;
** 	t_token_tree	*list;
**
** 	if (!cmd)
** 		return ;
** 	lexer = lexer_entry(cmd);
** 	list = build_list(lexer);
** 	lexer_delete(&lexer);
** 	if (!(list = build_token_tree(list))) // IDEA: error message could be nice.
** 		return ;
** 	// TODO: Reorganise tree(prioritising)
** 	execute_tree(sh, env, bin, list); // returns last return code
** 	clean_tree(list);
** }
*/
