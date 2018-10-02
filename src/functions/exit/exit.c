/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 20:04:47 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_exit(t_shell *sh, char **argv)
{
	int		status;
	size_t	argc;

	argc = ft_count_argv((void **)argv);
	if (argc > 1)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	status = (argc) ? ft_atoi(argv[0]) % 256 : 0;
	status = (status < 0) ? 256 + status : status;
	sh_delete(sh);
	exit(status);
	return (0);
}
