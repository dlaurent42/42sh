/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:39:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_env_add_item_noequal(t_shell *sh, t_env *env, char *key)
{
	char		*val;

	val = env_search(sh->local_env, key);
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_setenv_error(key, val, 4));
	env_insert(sh, env, key, val);
	return (0);
}

static char	sh_env_add_item_equal(t_shell *sh, t_env *env, char *arg)
{
	int			eq_sym;
	char		*key;
	char		*val;

	key = sh_setenv_parse(ft_strdups(arg));
	eq_sym = sh_setenv_equal(key);
	val = ft_strdups(ft_strchrsp(key, '='));
	key[eq_sym] = '\0';
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_setenv_error(key, val, 4));
	env_insert(sh, env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}

static char	sh_env_add_item(t_shell *sh, t_env *env, char *arg)
{
	if (!arg || arg[0] == '=')
		return (2);
	if (ft_strcountif(arg, '=') == 0)
		return (sh_env_add_item_noequal(sh, env, arg));
	return (sh_env_add_item_equal(sh, env, arg));
}

static void	sh_env_print(t_env *env)
{
	int	i;

	i = 0;
	while (env->environment[i])
	{
		ft_putendl(env->environment[i]);
		i++;
	}
	env_delete(env);
}

char		sh_env_display(t_shell *sh, t_env *env, char **arr, bool verbose)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (arr && arr[i] && res == 0)
	{
		(verbose) ? ft_printf("#env setenv:    %s\n", arr[i]) : 0;
		res = sh_env_add_item(sh, env, arr[i]);
		i++;
	}
	i = 0;
	if (arr)
		while (arr[i])
		{
			ft_strdel(&arr[i]);
			i++;
		}
	(arr) ? free(arr) : 0;
	(res == 0)
		? sh_env_print(env)
		: sh_env_error(env, NULL, NULL, res);
	return (res);
}
