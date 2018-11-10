/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 13:59:19 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:48:55 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	braclose(char *str, char c, int i, int b)
{
	while (b && *(++str) && (i++))
		if (*str == c)
			b++;
		else if (*str == (c == '(' ? ')' : c + 2))
			b--;
	return (i);
}

static char	open_b(char *str, char c)
{
	char status;

	if ((status = lexer_check_brackets(str + 1, ')')) != STATUS_OK)
		return (status == STATUS_ERR ? STATUS_ERR : STATUS_PARENTHESIS);
	else if ((status = lexer_check_brackets(str + braclose(str, *str, 1, 1), c))
			!= STATUS_OK)
		return (status);
	else
		return (STATUS_OK);
}

static char	open_c(char *str, char c)
{
	char status;

	if ((status = lexer_check_brackets(str + 1, '}')) != STATUS_OK)
		return (status == STATUS_ERR ? STATUS_ERR : STATUS_CURLY);
	else if ((status = lexer_check_brackets(str + braclose(str, *str, 1, 1), c))
			!= STATUS_OK)
		return (status);
	else
		return (STATUS_OK);
}

static char	open_s(char *str, char c)
{
	char status;

	if ((status = lexer_check_brackets(str + 1, ']')) != STATUS_OK)
		return (status == STATUS_ERR ? STATUS_ERR : STATUS_SQUARE);
	else if ((status = lexer_check_brackets(str + braclose(str, *str, 1, 1), c))
			!= STATUS_OK)
		return (status);
	else
		return (STATUS_OK);
}

char		lexer_check_brackets(char *str, char c)
{
	if (*str == c)
		return (STATUS_OK);
	else if (!*str)
		return (STATUS_WHEREISBRACKET);
	else if (*str == ')')
		return (STATUS_ERR);
	else if (*str == '}')
		return (STATUS_ERR);
	else if (*str == ']')
		return (STATUS_ERR);
	else if (*str == '(')
		return (open_b(str, c));
	else if (*str == '{')
		return (open_c(str, c));
	else if (*str == '[')
		return (open_s(str, c));
	else
		return (lexer_check_brackets(str + 1, c));
}
