/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:05:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 21:14:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_env_init_shell(t_shell *sh, char *path)
{
	char	*curr_path;
	char	*new_name;

	new_name = NULL;
	curr_path = NULL;
	curr_path = getcwd(curr_path, PATH_MAX);
	if (!env_search(sh->env, "SHELL") && sh->env->count + 1 >= sh->env->size)
		return ;
	new_name = ft_strjoins(curr_path, path + 1);
	env_insert(sh, sh->env, "SHELL", new_name);
	ft_strdel(&new_name);
	ft_strdel(&curr_path);
}
