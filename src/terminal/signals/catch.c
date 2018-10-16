/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:53:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 14:07:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int signo)
{
	if (signo == SIGWINCH)
		sh_window_resize(g_sh);
	if (signo == SIGINT && g_sh->pid > 0)
		kill(g_sh->pid, SIGKILL);
	else if (signo == SIGINT && g_sh->modes.multiline)
		sh_multilines_close(g_sh);
	else
		ft_putendl("^C");
}

void		signal_catching(void)
{
	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGWINCH\n");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGINT");
}
