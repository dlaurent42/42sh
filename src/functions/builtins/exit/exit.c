/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/08 16:23:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Exit from a program, shell or log out of a Unix network.
**
** -----------------------------------------------------------------------------
**
** Syntax
**       exit
**
** If supported will exit you from the program, shell or log you out of
** network.
**
** Alternatives: logout, lo, bye, quit, also Ctrl-D.
*/

char	sh_exit(t_shell *sh, t_env *env, char **argv)
{
	int		status;
	size_t	argc;

	(void)env;
	argc = ft_count_argv((void **)argv);
	if (argc > 1)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	status = (argc) ? ft_atoi(argv[0]) % 256 : 0;
	status = (status < 0) ? 256 + status : status;
	if (sh->env == env && sh->job == NULL)
	{
		sh_delete(sh);
		exit(status);
	}
	else if (sh->job != NULL)
	{
		ft_putendl_fd("sh: you have suspended jobs.", 2);
		return (0);
	}
	return (status);
}
