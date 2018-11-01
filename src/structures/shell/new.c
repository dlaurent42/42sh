/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:31:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 16:26:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_set_window(t_shell *sh)
{
	t_winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	sh->window.width = window.ws_col;
	sh->window.height = window.ws_row;
	ft_putstr(CLEAR_SCREEN);
	ft_putstr(CLEAR_HIST);
}

t_shell		*sh_new(char **environ)
{
	t_shell		*sh;

	if (!(sh = (t_shell *)ft_memalloc(sizeof(t_shell))))
		error_malloc_sh(sh);
	if (sh_set_termios(sh) != STATUS_OK)
		error_malloc_sh(sh);
	sh_set_window(sh);
	sh->env = env_new(sh, environ);
	env_initialize_local(sh);
	sh->alias = env_new(sh, NULL);
	sh_config_import(sh);
	sh->bin = bin_new(sh, sh->env);
	sh->read = read_new(sh);
	command_import(sh);
	sh_set_prompt(sh);
	if (!sh->prompt.content)
		error_malloc_sh(sh);
	g_sh = sh;
	return (sh);
}
