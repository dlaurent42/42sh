/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:26:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 12:17:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_history_option_c(t_shell *sh, t_env *env)
{
	ft_putendl("... history clearing start");
	command_delete_all(sh);
	remove(env_search(env, "HISTFILE"));
	ft_putendl("... history clearing end");
	return (0);
}
