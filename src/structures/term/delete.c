/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:53:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/05 20:47:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		term_delete(t_term *term)
{
	if (tcgetattr(0, term->termios) == -1)
		return ;
	term->termios->c_lflag = (ICANON | ECHO);
	tcsetattr(0, 0, term->termios);
	free(term->termios);
	ft_strdel(&term->header.content);
	free(term);
}
