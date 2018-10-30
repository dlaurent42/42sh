/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:57:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/30 14:03:46 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_dispatch_builtinsr(t_shell *sh, t_env *env, char **cmd)
{
	if (ft_strcmps(cmd[0], "alias") == 0)
		return (sh_alias(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "cd") == 0)
		return (sh_cd(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "echo") == 0)
		return (sh_echo(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "env") == 0)
		return (sh_env(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "exit") == 0)
		return (sh_exit(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "export") == 0)
		return (sh_export(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "history") == 0)
		return (sh_history(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "read") == 0)
		return (sh__read(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "setenv") == 0)
		return (sh_setenv(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "unalias") == 0)
		return (sh_unalias(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "unset") == 0)
		return (sh_unset(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "unsetenv") == 0)
		return (sh_unsetenv(sh, env, cmd + 1));
	return (-1);
}

static char	sh_command_exec(t_shell *sh, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	if ((sh->pid = fork()) == -1)
		return (-1);
	else if (sh->pid == 0)
		execve(cmd[0], cmd, env);
	else
	{
		signal_catching();
		pid = wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}

char		sh_command_dispatch(t_shell *sh, t_env *env, char **argv)
{
	char	res;

	if (!argv || !argv[0])
		return (1);
	if (env_search(env, "_") || env->count + 1 < env->size)
		env_insert(sh, env, "_", argv[0]);
	if (sh_is_not_builtin(argv[0]))
	{
		sh_unset_termios(sh);
		res = sh_command_exec(sh, argv, env->environment);
		sh_set_termios(sh);
	}
	else
		res = sh_command_dispatch_builtinsr(sh, env, argv);
	return (res);
}
