/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:37:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 11:55:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unset_remove(t_env *env, char *arg)
{
	char	*arg_parsed;

	arg_parsed = sh_unset_parse(ft_strdup(arg));
	if (!env || !env_search_local(env, arg_parsed))
		return (sh_unset_error(arg_parsed, 2));
	env_delete_item(env, arg_parsed);
	if (env_search_local(env, arg_parsed))
		return (sh_unset_error(arg_parsed, 3));
	ft_strdel(&arg_parsed);
	return (0);
}
