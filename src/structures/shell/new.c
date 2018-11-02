/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:31:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 17:22:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_set_window(t_shell *sh, int argc)
{
	t_winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	sh->window.width = window.ws_col;
	sh->window.height = window.ws_row;
	(void)argc;
	(argc == 1) ? ft_putstr(CLEAR_SCREEN) : 0;
	(argc == 1) ? ft_putstr(CLEAR_HIST) : 0;
}

t_shell		*sh_new(char **environ, int argc)
{
	t_shell		*sh;

	if (!(sh = (t_shell *)ft_memalloc(sizeof(t_shell))))
		error_malloc_sh(sh);
	if (sh_set_termios(sh) != STATUS_OK && argc == 1)
		error_malloc_sh(sh);
	sh_set_window(sh, argc);
	sh->env = env_new(sh, environ);
	env_initialize_local(sh);
	sh->alias = env_new(sh, NULL);
	sh_config_import(sh);
	sh->bin = bin_new(sh, sh->env);
	sh->read = read_new(sh);
	sh->modes.subshell = (argc > 1);
	command_import(sh);
	(!sh->modes.subshell) ? sh_set_prompt(sh) : 0;
	if (!sh->modes.subshell && !sh->prompt.content)
		error_malloc_sh(sh);
	g_sh = sh;
	return (sh);
}
