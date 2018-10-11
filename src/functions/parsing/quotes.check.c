/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:32:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 20:37:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	sh_command_quotes_check(t_shell *sh)
{
	int		i;
	int		n_dquote;
	int		n_squote;
	bool	in_dquote;
	bool	in_squote;

	i = 0;
	n_dquote = 0;
	n_squote = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (sh->buffer.parsed[i])
	{
	}
}
