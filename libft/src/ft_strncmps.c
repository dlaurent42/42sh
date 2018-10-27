/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/functions/lexer/lexer_entry.c
/*   Created: 2018/10/07 11:53:10 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 18:28:21 by azaliaus         ###   ########.fr       */
=======
/*   Created: 2018/04/03 14:57:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:44:54 by dlaurent         ###   ########.fr       */
>>>>>>> feat/heredoc:libft/src/ft_strncmps.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD:src/functions/lexer/lexer_entry.c
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
=======
int		ft_strncmps(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	return (ft_strncmp(s1, s2, n));
>>>>>>> feat/heredoc:libft/src/ft_strncmps.c
}
