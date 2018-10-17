/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:37:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 11:33:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unalias_remove(t_env *env, char *arg)
{
	char	*arg_parsed;

	arg_parsed = sh_parse_quotes(ft_strdup(arg));
	if (!env || !env_search(env, arg_parsed) || !env_key_is_ok(arg_parsed))
		return (sh_unalias_error(arg_parsed, 2));
	env_delete_item(env, arg_parsed);
	if (env_search(env, arg_parsed))
		return (sh_unalias_error(arg_parsed, 3));
	ft_strdel(&arg_parsed);
	return (0);
}
