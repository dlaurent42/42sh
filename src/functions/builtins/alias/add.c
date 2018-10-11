/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:43:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 16:48:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_alias_add(t_shell *sh, t_env *env, char *arg)
{
	int			eq_sym;
	char		*key;
	char		*val;

	if (!arg || arg[0] == '=' || ft_strcountif(arg, '=') == 0)
		return (sh_alias_error(NULL, NULL, 2, NULL));
	key = sh_alias_parse(ft_strdups(arg));
	eq_sym = sh_alias_equal(key);
	val = ft_strdups(ft_strchrsp(key, '='));
	key[eq_sym] = '\0';
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_alias_error(key, val, 4, NULL));
	env_insert(sh, env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}
