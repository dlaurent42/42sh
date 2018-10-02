/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 19:39:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_env_add_item(t_shell *sh, t_env *env, char *arg)
{
	int			eq_sym;
	char		*key;
	char		*val;

	key = NULL;
	val = NULL;
	sh_debug(NULL, ft_strjoins(".. adding", arg), NULL);
	if (!arg || arg[0] == '=' || ft_strcountif(arg, '=') == 0)
		return (2);
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

char		sh_env_display(t_shell *sh, t_env *env, char *string)
{
	int		i;
	int		res;
	char	**strsplt;

	i = 0;
	res = 0;
	strsplt = ft_strsplit(string, ' ');
	sh_debug(NULL, "display", NULL);
	sh_debug(NULL, string, NULL);
	while (strsplt && strsplt[i] && res == 0)
	{
		res = sh_env_add_item(sh, env, strsplt[i]);
		i++;
	}
	i = 0;
	if (strsplt)
		while (strsplt[i])
		{
			ft_strdel(&strsplt[i]);
			i++;
		}
	(strsplt) ? free(strsplt) : 0;
	(res == 0)
		? sh_env_print(env)
		: sh_env_error(env, NULL, NULL, res);
	return (res);
}
