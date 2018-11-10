/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 11:22:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_env_exec(t_shell *sh, t_env *env, t_bin *bin, char **arr)
{
	execute_subshell_env(env, arr);
	env_delete(env);
	bin_delete(bin);
	return (ft_atoi(env_search(sh->env, "?")));
}
