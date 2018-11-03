/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:06:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/03 20:30:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_config(t_shell *sh)
{
	char		*file;
	char		*home;
	char		*name;

	if (env_search(sh->env, "CONFIG") || sh->env->count + 1 >= sh->env->size)
		return ;
	if (!(home = env_search(sh->env, "HOME")))
		return ;
	if (!(name = env_search(sh->env, "0")))
		return ;
	if (!(file = ft_strjoins(home, "/.")))
		return ;
	if (!(file = ft_strjoinf(file, name, 1)))
		return ;
	if (!(file = ft_strjoinf(file, "rc", 1)))
		return ;
	env_insert_local(sh, sh->env, "CONFIG", file);
	ft_strdel(&file);
}
