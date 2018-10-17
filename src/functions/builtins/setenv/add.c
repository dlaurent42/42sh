/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:00:52 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 15:37:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_setenv_add_noequal(t_shell *sh, t_env *env, char *key)
{
	if (!env_key_is_ok(key))
		return (sh_setenv_error(NULL, NULL, 2, NULL));
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_setenv_error(NULL, NULL, 4, NULL));
	env_insert(sh, env, key, "");
	return (0);
}

static char	sh_setenv_add_equal(t_shell *sh, t_env *env, char *arg)
{
	int			bin;
	int			eq_sym;
	char		*key;
	char		*val;
	t_bin_obj	*obj;

	bin = sh_is_binary(arg);
	key = sh_parse_quotes(ft_strdups(arg));
	eq_sym = sh_get_equal_position(key);
	val = (bin)
		? ft_strdups(arg + bin) : ft_strdups(ft_strchrsp(key, '='));
	key[eq_sym] = '\0';
	if (!env_key_is_ok(key))
		return (sh_setenv_error(key, val, 2, NULL));
	if (bin && !(obj = bin_search(sh->bin, val)))
		return (sh_setenv_error(key, val, 3, NULL));
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_setenv_error(key, val, 4, NULL));
	(bin)
		? env_insert(sh, env, key, obj->path)
		: env_insert(sh, env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}

char		sh_setenv_add(t_shell *sh, t_env *env, char *arg)
{
	if (!arg || arg[0] == '=')
		return (sh_setenv_error(NULL, NULL, 2, NULL));
	if (ft_strcountif(arg, '=') == 0)
		return (sh_setenv_add_noequal(sh, env, arg));
	return (sh_setenv_add_equal(sh, env, arg));
}
