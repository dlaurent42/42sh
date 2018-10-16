/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:43:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 14:15:33 by dlaurent         ###   ########.fr       */
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

void	sh_set_termios(t_shell *sh)
{
	char		*name;

	name = (getenv("TERM")) ? getenv("TERM") : "xterm-256color";
	if (tgetent(NULL, name) == ERR)
		return (error_malloc_sh(sh));
	if (tcgetattr(STDIN_FILENO, &(sh->termios)) == -1)
		return (error_malloc_sh(sh));
	sh->termios.c_lflag &= ~(ICANON);
	sh->termios.c_lflag &= ~(ECHO);
	sh->termios.c_cc[VMIN] = 1;
	sh->termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(sh->termios)) == -1)
		error_malloc_sh(sh);
}
