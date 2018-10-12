/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 19:58:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	sh_command_lexer(t_shell *sh, t_env *env, char *str)
{
	if (!sh_command_parse_backslash(str))
		return (FALSE);
	if (!sh_command_quotes_check(str))
		return (FALSE);
	sh_command_expand_dollars(sh, env, str);
	sh_command_expand_tile(sh, env, str);
	sh_command_trim(str);
	return (TRUE);
}
