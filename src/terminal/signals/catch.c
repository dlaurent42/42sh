/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:53:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/07 13:28:29 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int signo)
{
	if (signo == SIGWINCH)
		sh_window_resize(g_sh);
	if (signo == SIGINT && g_sh->pid > 0)
		kill(g_sh->pid, SIGKILL);
	else if (signo == SIGINT && g_sh->modes.multiline && !g_sh->modes.subshell)
		sh_multilines_close(g_sh);
	else if (signo == SIGINT && !g_sh->modes.exec && !g_sh->modes.globbing
	&& !g_sh->modes.auto_completion && !g_sh->modes.subshell)
		sh_sigint_reset(g_sh, "1");
}

void		sig_job(int signo)
{
	(void)signo;
	ft_putendl_fd("Got signal from CTRL + Z", 2);
	if (!g_sh->job)
	{
		ft_putendl_fd("There is no job to do!", 2);
		// kill(g_sh->pid, SIGTSTP);
	}
}

void		signal_catching(void)
{
	signal(SIGSEGV, sig_handler);
	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
		ft_putendl_fd("\ncan't catch SIGWINCH", 2);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putendl_fd("\ncan't catch SIGINT", 2);
	(g_sh->job) ? signal(SIGTSTP, sig_job) : signal(SIGTSTP, SIG_DFL);
	// ADDED ONLY FOR TESTING
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGTSTP, SIG_IGN);
	// signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	// signal(SIGCHLD, SIG_IGN);
}
