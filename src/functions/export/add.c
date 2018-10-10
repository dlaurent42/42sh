/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:09:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:41:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_export_add_noequal(t_shell *sh, t_env *env, char *key)
{
	char		*val;

	val = env_search(sh->local_env, key);
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_export_error(NULL, NULL, 4, NULL));
	env_insert(sh, env, key, val);
	return (0);
}

static char	sh_export_add_equal(t_shell *sh, t_env *env, char *arg)
{
	int			bin;
	int			eq_sym;
	char		*key;
	char		*val;
	t_bin_obj	*obj;

	bin = sh_export_isbin(arg);
	key = sh_export_parse(ft_strdups(arg));
	eq_sym = sh_setenv_equal(key);
	val = (bin)
		? ft_strdups(arg + bin) : ft_strdups(ft_strchrsp(key, '='));
	key[eq_sym] = '\0';
	if (bin && !(obj = bin_search(sh->bin, val)))
		return (sh_export_error(key, val, 3, NULL));
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_export_error(key, val, 4, NULL));
	(bin)
		? env_insert(sh, env, key, obj->path)
		: env_insert(sh, env, key, val);
	if (env_search(sh->local_env, key))
		env_insert(sh, sh->local_env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}

char	sh_export_add(t_shell *sh, t_env *env, char *arg)
{
	if (!arg || arg[0] == '=')
		return (sh_export_error(NULL, NULL, 2, NULL));
	if (ft_strcountif(arg, '=') == 0)
		return (sh_export_add_noequal(sh, env, arg));
	return (sh_export_add_equal(sh, env, arg));
}
