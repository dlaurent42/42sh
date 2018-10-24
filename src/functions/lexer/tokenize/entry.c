/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 11:53:10 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 12:52:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_entry(t_shell *sh, t_env *env, char *cmd)
{
	char	status;
	t_lexer lexer;

	(void)env;
	status = 0;
	ft_bzero((void *)&lexer, sizeof(t_lexer));
	lexer_fill(&lexer, cmd); // A remplacer par ce qu'il y a ci-dessous
//	if ((status = lexer_fill(&lexer, cmd)) != 0)
//		lexer_delete(&lexer);
	sh->lexer = lexer;
	return (status);
}
