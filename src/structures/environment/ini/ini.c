/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:59:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 12:31:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_initialize_local(t_shell *sh)
{
	sh_env_init_home(sh);
	sh_env_init_config(sh);
	sh_env_init_histfile(sh);
	sh_env_init_ppid(sh);
	sh_env_init_ps(sh);
	sh_env_init_pwd(sh);
	sh_env_init_shlvl(sh);
	sh_env_init_specials(sh);
	sh_env_init_term(sh);
}
