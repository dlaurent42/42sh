/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:30:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/23 21:09:26 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_build_tree(char *cmd)
{
	t_lexer			lexer;
	t_token_tree	*list;

	lexer = lexer_entry(cmd);
	list = build_list(lexer);

	lexer_delete(&lexer);
}
