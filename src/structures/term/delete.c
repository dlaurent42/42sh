/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:53:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 22:25:18 by dlaurent         ###   ########.fr       */
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
	if (term->prompt.content)
		ft_strdel((char **)&term->prompt.content);
	if (term->prompt.location)
		ft_strdel((char **)&term->prompt.location);
	free(term);
}
