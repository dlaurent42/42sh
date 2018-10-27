/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree_token_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:23:01 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 13:49:56 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 0 - CMD
** 6 - ;
** 5 - || or &&
** 4 - |
** 3 - >&
** 2 - < or <<
** 1 - > or >>
*/
/*
** TODO: change to token type. On merge
*/
size_t			get_tree_token_type(t_token token)
{
	size_t			type;

	type  = 0;
	type = (token.type == TOKEN_SEMICOLON ? 6 : type);
	type = (token.type == TOKEN_ORIF || token.type == TOKEN_ANDIF ? 5 : type);
	type = (token.type == TOKEN_PIPE ? 4 : type);
	type = (token.type == TOKEN_AGGREG ? 3 : type);
	type = (token.type == TOKEN_AGGREG || token.type == TOKEN_AGGREG) ? 2 : type);
	type = (!ft_strcmp(token.id, ">") || !ft_strcmp(token.id, ">>") ? 1 : type);
	type = (!ft_strcmp(token.id, ">") || !ft_strcmp(token.id, ">>") ? 1 : type);
	return (type);
}
