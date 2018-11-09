/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:59:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 21:11:49 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_exe_name(char *name)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (name[i])
	{
		if (name[i] == '/' && !lexer_is_esc(name, i))
			j = i + 1;
		i++;
	}
	return (j);
}

void		env_initialize_local(t_shell *sh, char *name)
{
	char	*realname;

	if (!sh)
		return ;
	realname = ft_strdups(name + get_exe_name(name));
	sh_env_init_home(sh);
	sh_env_init_shell(sh, name);
	sh_env_init_specials(sh, realname);
	sh_env_init_config(sh);
	sh_env_init_histfile(sh);
	sh_env_init_ppid(sh);
	sh_env_init_ps(sh);
	sh_env_init_pwd(sh);
	sh_env_init_shlvl(sh);
	sh_env_init_term(sh);
	ft_strdel(&realname);
}
