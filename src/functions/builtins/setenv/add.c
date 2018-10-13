/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:00:52 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 18:53:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_setenv_add(t_shell *sh, t_env *env, char *arg)
{
	int			bin;
	int			eq_sym;
	char		*key;
	char		*val;
	t_bin_obj	*obj;

	if (!arg || arg[0] == '=' || ft_strcountif(arg, '=') == 0)
		return (sh_setenv_error(NULL, NULL, 2));
	bin = sh_setenv_isbin(arg);
	key = sh_setenv_parse(ft_strdups(arg));
	eq_sym = sh_setenv_equal(key);
	val = (bin)
		? ft_strdups(arg + bin) : ft_strdups(ft_strchrsp(key, '='));
	key[eq_sym] = '\0';
	if (env_search_local(env, key))
		return (sh_setenv_error(key, val, 3));
	if (bin && !(obj = bin_search(sh->bin, val)))
		return (sh_setenv_error(key, val, 4));
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_setenv_error(key, val, 5));
	(bin) ? env_insert(sh, env, key, obj->path) : env_insert(sh, env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}
