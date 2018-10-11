/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:40:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 21:07:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_command_replace_backslash_octal(t_shell *sh, int i)
{
	int	j;
	int	val;

	j = i + 1;
	val = 0;
	while (ft_isdigit(sh->buffer.parsed[j]) && j <= i + 3)
	{
		val = val * 8 + (sh->buffer.parsed[j] - 48);
		j++;
	}
	if (val > 127)
		return ;
	sh->buffer.parsed[i] = val;
	sh_command_repatriate(sh, i + 1, j - i);
}

static bool	sh_command_replace_backslah(t_shell *sh, int i)
{
	bool	is_escaped;

	is_escaped = FALSE;
	if (sh->buffer.parsed[i + 1] == '\0')
		return (FALSE);
	if (sh->buffer.parsed[i + 1] == '\\' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\\';
	else if (sh->buffer.parsed[i + 1] == 'a' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\a';
	else if (sh->buffer.parsed[i + 1] == 'b' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\b';
	else if (sh->buffer.parsed[i + 1] == 'f' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\f';
	else if (sh->buffer.parsed[i + 1] == 'n' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\n';
	else if (sh->buffer.parsed[i + 1] == 'r' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\r';
	else if (sh->buffer.parsed[i + 1] == 't' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\t';
	else if (sh->buffer.parsed[i + 1] == 'v' && (is_escaped = TRUE))
		sh->buffer.parsed[i] = '\v';
	(is_escaped)
		? sh_command_repatriate(sh, i + 1, 1)
		: sh_command_replace_backslash_octal(sh, i);
	return (TRUE);
}

bool		sh_command_parse_backslash(t_shell *sh)
{
	int		i;
	int		n_backslash;
	bool	in_dquote;
	bool	in_squote;
	bool	prev_is_backslash;

	i = 0;
	n_backslash = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	prev_is_backslash = FALSE;
	while (sh->buffer.parsed[i])
	{
		if (sh->buffer.parsed[i] == '"')
			in_dquote = (in_dquote) ? FALSE : TRUE;
		if (sh->buffer.parsed[i] == '\'')
			in_squote = (in_squote) ? FALSE : TRUE;
		if (sh->buffer.parsed[i] == '\\')
	}
}
