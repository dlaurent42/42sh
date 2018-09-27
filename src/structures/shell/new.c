/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:31:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 15:52:07 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_set_termios(t_shell *sh)
{
	if (!(sh->termios = (t_termios *)ft_memalloc(sizeof(t_termios))))
		error_malloc_sh(sh);
	(tcgetattr(0, sh->termios) == -1) ? error_malloc_sh(sh) : 0;
	sh->termios->c_lflag &= ~(ICANON);
	sh->termios->c_lflag &= ~(ECHO);
	sh->termios->c_cc[VMIN] = 1;
	sh->termios->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, sh->termios) == -1)
		error_malloc_sh(sh);
}

static void	sh_init_prompt(t_shell *sh)
{
	sh_set_prompt(sh);
	if (!sh->prompt.content)
		error_malloc_sh(sh);
}

t_shell		*sh_new(char **environ)
{
	char		*name;
	t_shell		*sh;
	t_winsize	window;

	if (!(sh = (t_shell *)ft_memalloc(sizeof(t_shell))))
		error_malloc_sh(sh);
	(!(name = getenv("TERM"))) ? error_malloc_sh(sh) : 0;
	(tgetent(NULL, name) == ERR) ? error_malloc_sh(sh) : 0;
	sh_set_termios(sh);
	ft_putstr(CLEAR_SCREEN);
	ft_putstr("\e[3J");
	ioctl(0, TIOCGWINSZ, &window);
	sh->window.width = window.ws_col;
	sh->window.height = window.ws_row;
	sh->env = env_new(sh, environ);
	sh->bin = bin_new(sh);
	sh->read = read_new(sh);
	command_import(sh);
	sh_init_prompt(sh);
	return (sh);
}
