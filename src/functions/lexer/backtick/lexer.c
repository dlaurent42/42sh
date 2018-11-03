/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:36:28 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/03 13:53:27 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lexer_glob	*add_node_lexer_backtick(
	t_lexer_glob *current, char *s, int type)
{
	int			i;
	char		**arr;

	i = 0;
	arr = lexer_strsplit_ws(s);
	while (arr && arr[i])
	{
		current = add_node_lexer_glob(current, arr[i], type);
		i++;
	}
	ft_strdel(&s);
	(arr) ? free(arr) : 0;
	return (current);
}
