/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:53:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 20:09:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
		ft_printf("received SIGUSR1\n");
	else if (signo == SIGTSTP)
		ft_printf("received SIGKILL\n");
	else if (signo == SIGQUIT)
		ft_printf("received SIGSTOP\n");
	else if (signo == SIGQUIT)
		ft_printf("received SIGSTOP\n");
	else if (signo == SIGWINCH)
		return ;
	else
		ft_printf("another signal (%d) received\n", signo);
}

void		signal_catching(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGINT\n");
	if (signal(SIGTSTP, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGTSTP\n");
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGQUIT\n");
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGUSR1\n");
	if (signal(SIGUSR2, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGUSR2\n");
	if (signal(SIGABRT, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGABRT\n");
	if (signal(SIGILL, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGILL\n");
	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGWINCH\n");
}
