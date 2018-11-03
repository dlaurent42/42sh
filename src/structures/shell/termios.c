/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:43:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 17:22:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_unset_termios(t_shell *sh)
{
	tcgetattr(0, &(sh->termios));
	sh->termios.c_lflag |= (ICANON);
	sh->termios.c_lflag |= (ECHO);
	sh->termios.c_cc[VTIME] = 0;
	sh->termios.c_cc[VMIN] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(sh->termios));
}

char	sh_set_termios(t_shell *sh)
{
	char		*name;

	name = (getenv("TERM")) ? getenv("TERM") : TERM_DEFAULT;
	if (tgetent(NULL, name) == STATUS_ERR)
		return (STATUS_ERR);
	if (tcgetattr(STDIN_FILENO, &(sh->termios)) == STATUS_ERR)
		return (STATUS_ERR);
	sh->termios.c_lflag &= ~(ICANON);
	sh->termios.c_lflag &= ~(ECHO);
	sh->termios.c_cc[VMIN] = 1;
	sh->termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(sh->termios)) == STATUS_ERR)
		return (STATUS_ERR);
	return (STATUS_OK);
}
