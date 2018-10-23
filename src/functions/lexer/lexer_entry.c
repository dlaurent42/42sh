/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 11:53:10 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 18:28:21 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// #include <stdio.h>

t_lexer		lexer_entry(char *cmd)
{
	t_lexer lexer;

	ft_bzero((void *)&lexer, sizeof(t_lexer));
	lexer_fill(&lexer, cmd);
	return (lexer);

	// insert
	// // size_t i = 0;
	// // while (i < lexer.size)
	// // {
	// // 	printf("Token: %s | Type: %d\n", lexer.tokens[i].id, lexer.tokens[i].type);
	// // 	i++;
	// }
	// /insert


	// lexer_delete(&lexer);
}
