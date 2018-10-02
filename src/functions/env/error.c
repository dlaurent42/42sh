/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:01:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 18:24:10 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_env_error(t_env *env, char *s1, char *s2, int err_id)
{
	if (env)
		env_delete(env);
	if (err_id == -1)
		ft_putendl_fd("env: unsetenv: Invalid arguments", 2);
	if (err_id == -2)
		ft_putendl_fd("env: unsetenv: not enough arguments", 2);
	if (err_id == -3)
		ft_putendl_fd("env: option requires an argument -- P", 2);
	if (err_id == -4)
		ft_putendl_fd("env: option requires an argument -- S", 2);
	if (err_id == 2)
		ft_putendl_fd("env: setenv: wrong argument", 2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (1);
}
