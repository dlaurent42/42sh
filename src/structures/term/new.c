/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:54:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 03:01:31 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term	*term_new(t_shell *shell)
{
	char		*name;
	t_term		*term;

	if (!(name = getenv("TERM")))
		error_no_term_var(shell);
	if (tgetent(NULL, &name_term) == ERR)
		error_no_term_var(shell);
	if (tcgetattr(0, term) == -1)
		error_no_term_var(shell);
}
