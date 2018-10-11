/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:37:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 17:13:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unset_remove(t_env *env, char *arg)
{
	char	*arg_parsed;

	arg_parsed = sh_unset_parse(ft_strdup(arg));
	sh_debug(NULL, env_search_local(env, arg_parsed), NULL);
	if (!env || !env_search_local(env, arg_parsed))
		return (sh_unset_error(arg_parsed, 2));
	env_delete_item(env, arg_parsed);
	if (env_search_local(env, arg_parsed))
		return (sh_unset_error(arg_parsed, 3));
	ft_strdel(&arg_parsed);
	return (0);
}
