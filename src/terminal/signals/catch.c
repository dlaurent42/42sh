/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:53:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/08 14:30:59 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int signo)
{
	if (signo == SIGWINCH)
		sh_window_resize(g_sh);
	if (signo == SIGINT && g_sh->pid > 0)
		kill(g_sh->pid, SIGINT);
	else if (signo == SIGINT && g_sh->modes.multiline && !g_sh->modes.subshell)
		sh_multilines_close(g_sh);
	else if (signo == SIGINT && !g_sh->modes.exec && !g_sh->modes.globbing
	&& !g_sh->modes.auto_completion && !g_sh->modes.subshell)
		sh_sigint_reset(g_sh, "1");
}

void		signal_catching(void)
{
	signal(SIGSEGV, sig_handler);
	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
		ft_putendl_fd("\ncan't catch SIGWINCH", 2);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putendl_fd("\ncan't catch SIGINT", 2);
	signal(SIGTSTP, SIG_IGN);
	(g_sh->jc) ? signal(SIGTTOU, SIG_IGN) : (0);
}
