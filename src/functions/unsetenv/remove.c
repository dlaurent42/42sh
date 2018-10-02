/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 10:16:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 20:46:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unsetenv_remove(t_shell *sh, char *arg)
{
	char	*arg_parsed;

	arg_parsed = sh_unsetenv_parse(ft_strdup(arg));
	if (!env_search(sh->env, arg_parsed))
		return (sh_unsetenv_error(arg_parsed, 2));
	env_delete_item(sh->env, arg_parsed);
	if (env_search(sh->env, arg_parsed))
		return (sh_unsetenv_error(arg_parsed, 3));
	ft_strdel(&arg_parsed);
	return (0);
}
