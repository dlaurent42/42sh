/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:31:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 15:46:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_set_termios(t_shell *sh)
{
	t_winsize	window;

	if (!(sh->termios = (t_termios *)ft_memalloc(sizeof(t_termios))))
		error_malloc_sh(sh);
	(tcgetattr(0, sh->termios) == -1) ? error_malloc_sh(sh) : 0;
	sh->termios->c_lflag &= ~(ICANON);
	sh->termios->c_lflag &= ~(ECHO);
	sh->termios->c_cc[VMIN] = 1;
	sh->termios->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, sh->termios) == -1)
		error_malloc_sh(sh);
	ioctl(0, TIOCGWINSZ, &window);
	sh->window.width = window.ws_col;
	sh->window.height = window.ws_row;
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

	if (!(sh = (t_shell *)ft_memalloc(sizeof(t_shell))))
		error_malloc_sh(sh);
	(!(name = getenv("TERM"))) ? error_malloc_sh(sh) : 0;
	(tgetent(NULL, name) == ERR) ? error_malloc_sh(sh) : 0;
	sh_set_termios(sh);
	ft_putendl("Building environment");
	sh->env = env_new(sh, environ);
	ft_putendl("Building aliases");
	sh->alias = env_new(sh, NULL);
	ft_putendl("Local variables initialization");
	env_initialize_local(sh);
	ft_putendl("Importing binaries from PATH");
	sh->bin = bin_new(sh);
	sh->read = read_new(sh);
	ft_putendl("Importing command history");
	command_import(sh);
	ft_putendl("Prompt initialization");
	sh_init_prompt(sh);
	g_sh = sh;
	return (sh);
}
