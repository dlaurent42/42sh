/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orga.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 13:39:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 15:20:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_heredoc_repatriate_loop(t_lexer *lexer, int i, int cmd_pos)
{
	int				j;
	int				tmp_blank;
	char			*tmp_id;
	t_token_type	tmp_type;

	j = i;
	tmp_id = ft_strdups(lexer->tokens[i].id);
	tmp_type = lexer->tokens[i].type;
	tmp_blank = lexer->tokens[i].blank_before;
	while (cmd_pos + 1 <= j)
	{
		ft_strdel(&(lexer->tokens[j].id));
		lexer->tokens[j].id = ft_strdups(lexer->tokens[j - 1].id);
		lexer->tokens[j].type = lexer->tokens[j - 1].type;
		lexer->tokens[j].blank_before = lexer->tokens[j - 1].blank_before;
		j--;
	}
	ft_strdel(&(lexer->tokens[j].id));
	lexer->tokens[cmd_pos].id = tmp_id;
	lexer->tokens[cmd_pos].type = tmp_type;
	lexer->tokens[cmd_pos].blank_before = tmp_blank;
}

static void	sh_heredoc_repatriate(t_lexer *lexer, int i, int cmd_pos)
{
	i += 2;
	while (i < (int)lexer->size
	&& (lexer->tokens[i].type == TOKEN_SINGLEQUOTE
	|| lexer->tokens[i].type == TOKEN_DOUBLEQUOTE
	|| lexer->tokens[i].type == TOKEN_BACKQUOTE
	|| lexer->tokens[i].type == TOKEN_WORD))
	{
		sh_heredoc_repatriate_loop(lexer, i, cmd_pos);
		cmd_pos++;
		i++;
	}
}

char		sh_heredoc_orga(t_lexer *lexer, char status)
{
	int		i;
	int		command_position;

	i = 0;
	command_position = 0;
	if (status != STATUS_OK)
		return (status);
	while (i < (int)lexer->size)
	{
		if (lexer->tokens[i].type == TOKEN_ANDIF
		|| lexer->tokens[i].type == TOKEN_ORIF
		|| lexer->tokens[i].type == TOKEN_PIPE
		|| lexer->tokens[i].type == TOKEN_SEMICOLON)
			command_position = i;
		if (lexer->tokens[i].type == TOKEN_SINGLEQUOTE
		|| lexer->tokens[i].type == TOKEN_DOUBLEQUOTE
		|| lexer->tokens[i].type == TOKEN_BACKQUOTE
		|| lexer->tokens[i].type == TOKEN_WORD)
			command_position++;
		else if (lexer->tokens[i].type == TOKEN_HEREDOC)
			sh_heredoc_repatriate(lexer, i, command_position);
		i++;
	}
	return (status);
}
