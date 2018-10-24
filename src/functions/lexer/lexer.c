/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 12:38:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_command_lexer(t_shell *sh)
{
	char	*str;
	t_env	*env;

	ft_bzero(sh->buffer.parsed, ARG_MAX);
	ft_strcpy(sh->buffer.parsed, sh->buffer.content);
	str = sh->buffer.parsed;
	env = sh->env;
	if (sh->modes.heredoc == FALSE)
		return (lexer_entry(sh, str));
	return (sh_heredoc(sh, NULL));
}
