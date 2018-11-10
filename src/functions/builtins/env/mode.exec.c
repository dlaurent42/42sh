/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 17:13:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_env_exec_get_str(char **arr)
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
	return (str);
}

char		sh_env_exec(t_shell *sh, t_env *env, t_bin *bin, char **arr)
{
	t_shell	*nsh;
	char	*str;
	char	status;

	(void)sh;
	if (!(nsh = (t_shell *)ft_memalloc(sizeof(t_shell))))
		return (sh_env_error(env, bin, 0, 6));
	if (!(str = sh_env_exec_get_str(arr)))
		return (sh_env_error(env, bin, 0, 6));
	status = sh_command_run(nsh, env, bin, &str);
	free(nsh);
	ft_strdel(&str);
	env_delete(env);
	bin_delete(bin);
	return (status);
}
