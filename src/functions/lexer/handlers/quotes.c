/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:32:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 14:28:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_check_squote(int *n_squote, bool *in_squote, bool *in_dquote)
{
	*n_squote += (*in_dquote) ? 0 : 1;
	*in_squote = (*in_dquote || *in_squote) ? FALSE : TRUE;
}

static void	sh_check_dquote(int *n_dquote, bool *in_squote, bool *in_dquote)
{
	*n_dquote += (*in_squote) ? 0 : 1;
	*in_dquote = (*in_dquote || *in_squote) ? FALSE : TRUE;
}

bool		sh_command_quotes_check(char *str)
{
	int		i;
	int		n_dquote;
	int		n_squote;
	bool	in_dquote;
	bool	in_squote;

	i = -1;
	n_dquote = 0;
	n_squote = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (str[++i])
		if (str[i] == '"')
			sh_check_dquote(&n_dquote, &in_squote, &in_dquote);
		else if (str[i] == '\'')
			sh_check_squote(&n_squote, &in_squote, &in_dquote);
		else if (str[i] == ';')
		{
			if (n_dquote % 2 || n_squote % 2)
				return (FALSE);
			return (sh_command_quotes_check(str + i + 1));
		}
	return (!(n_dquote % 2 || n_squote % 2));
}
