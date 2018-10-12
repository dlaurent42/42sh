/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:01:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 00:39:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_env_usage(void)
{
	ft_putendl_fd("usage: env [-i] [-u name]", 2);
	ft_putendl_fd("       [name=value ...] [utility [argument ...]]", 2);
}

char		sh_env_error(t_env *env, t_bin *bin, char c, int err_id)
{
	if (env)
		env_delete(env);
	if (bin)
		bin_delete(bin);
	if (err_id == 1)
		ft_putendl_fd("env: unsetenv: not enough arguments", 2);
	if (err_id == 2)
		ft_putendl_fd("env: unsetenv: Invalid arguments", 2);
	if (err_id == 3)
		ft_putendl_fd("env: option requires an argument -- u", 2);
	if (err_id == 4)
	{
		ft_putstr_fd("env: illegal option or use of option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
	}
	if (err_id == 5)
		ft_putendl_fd("env: setenv: wrong argument", 2);
	if (err_id == 6)
		ft_putendl_fd("env: error in lexer", 2);
	sh_env_usage();
	return (1);
}
