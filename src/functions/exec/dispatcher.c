/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 13:52:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 20:58:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_dispatch_builtins(t_shell *sh, t_env *env, char **argv)
{
	if (ft_strcmps(argv[0], "alias") == 0)
		return (sh_alias(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "cd") == 0)
		return (sh_cd(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "echo") == 0)
		return (sh_echo(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "env") == 0)
		return (sh_env(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "exit") == 0)
		return (sh_exit(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "export") == 0)
		return (sh_export(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "history") == 0)
		return (sh_history(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "setenv") == 0)
		return (sh_setenv(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "unalias") == 0)
		return (sh_unalias(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "unset") == 0)
		return (sh_unset(sh, env, argv + 1));
	if (ft_strcmps(argv[0], "unsetenv") == 0)
		return (sh_unsetenv(sh, env, argv + 1));
	return (0);
}

char		sh_command_dispatch(t_shell *sh, t_env *env, char **argv)
{
	char	res;

	if (!argv || !argv[0])
		return (1);
	if (!sh_is_not_builtin(argv[0]))
		return (sh_command_dispatch_builtins(sh, env, argv));
	res = sh_command_exec(sh, argv, env->environment);
	return (res);
}
