/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 11:53:10 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 16:04:33 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_entry(char *cmd)
{
	t_lexer lexer;

	ft_bzero((void *)&lexer, sizeof(t_lexer));
	lexer_fill(&lexer, cmd);
	lexer_delete(&lexer);
}
