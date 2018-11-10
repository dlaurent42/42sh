/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree_token_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:23:01 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 15:58:13 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 7 - ;
** 6 - ||
** 5 - &&
** 4 - |
** 3 - >&
** 2 - < or <<
** 1 - > or >>
** 0 - CMD
*/

size_t			get_tree_token_type(t_token token)
{
	size_t			type;

	type = 0;
	type = (token.type == TOKEN_SEMICOLON ? 7 : type);
	type = (token.type == TOKEN_ORIF ? 6 : type);
	type = (token.type == TOKEN_ANDIF ? 5 : type);
	type = (token.type == TOKEN_PIPE ? 4 : type);
	type = (token.type == TOKEN_AGGREG ? 3 : type);
	type = ((!ft_strcmp(token.id, "<") || (!ft_strcmp(token.id + 1, "<"))) ||
			((!ft_strcmp(token.id, "<<")) || (!ft_strcmp(token.id + 1, "<<"))) ?
			2 : type);
	type = ((!ft_strcmp(token.id, ">") || (!ft_strcmp(token.id + 1, ">"))) ||
			((!ft_strcmp(token.id, ">>")) || (!ft_strcmp(token.id + 1, ">>"))) ?
			1 : type);
	return (type);
}
