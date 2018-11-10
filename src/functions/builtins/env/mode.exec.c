/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 15:26:40 by dlaurent         ###   ########.fr       */
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
	char	*shlvl;
	char	**new_arr;

	if (!arr)
		return (STATUS_OK);
	if (!(new_arr = (char **)ft_memalloc(sizeof(char *) * 3)))
		return (sh_env_error(env, bin, 0, 6));
	new_arr[0] = ft_strdups(env_search(sh->env, "0"));
	new_arr[1] = sh_env_exec_get_str(arr);
	if (ft_atoi(env_search(env, "SHLVL")))
	{
		shlvl = ft_itoa(ft_atoi(env_search(env, "SHLVL")) - 1);
		env_insert(sh, env, "SHLVL", shlvl);
		ft_strdel(&shlvl);
	}
	execute_subshell_env(env, new_arr);
	ft_strdel(&new_arr[0]);
	ft_strdel(&new_arr[1]);
	free(new_arr);
	env_delete(env);
	bin_delete(bin);
	return (ft_atoi(env_search(sh->env, "?")));
}
