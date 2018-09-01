/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:54:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 20:43:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term	*term_new(t_shell *shell)
{
	char		*name;
	t_term		*term;

	if (!(name = getenv("TERM")))
		error_no_term_var(shell);
	if (tgetent(NULL, name) == ERR)
		error_no_term_var(shell);
	if (!(term = (t_term *)ft_memalloc(sizeof(t_term))))
		error_malloc_term(shell, "t_term");
	if (tcgetattr(0, term) == -1)
	{
		free(term);
		error_no_term_var(shell);
	}
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
	{
		free(term);
		error_no_term_var(shell);
	}
	ft_printf(tgetstr("cl", NULL));
	ft_printf(tgetstr("cl", NULL));
	return (term);
}
