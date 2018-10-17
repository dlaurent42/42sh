/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 22:52:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_env_exec_get_str(t_shell *sh, t_env *env, char **arr)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (arr[i])
	{
		str = (str) ? ft_strjoinf(str, " ", 1) : 0;
		str = ft_strjoinf(str, arr[i], 1);
		i++;
	}
	if (!sh_command_lexer(sh, env, str))
	{
		ft_strdel(&str);
		return (NULL);
	}
	return (str);
}

char		sh_env_exec(t_shell *sh, t_env *env, t_bin *bin, char **arr)
{
	char	*str;

	if (!(str = sh_env_exec_get_str(sh, env, arr)))
		return (sh_env_error(env, bin, 0, 6));
	sh_command_parser(sh, env, bin, str);
	ft_strdel(&str);
	env_delete(env);
	bin_delete(bin);
	return (sh->prompt.last_exec_succeed);
}
