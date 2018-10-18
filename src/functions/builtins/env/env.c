/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 14:06:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Display, set, or remove environment variables, Run a command in a modified
** environment.
**
** -----------------------------------------------------------------------------
**
** Syntax
**       env [OPTION]... [NAME=VALUE]... [COMMAND [ARGS]...]
**
** Options
**
**    -u NAME   Remove variable NAME from the environment, if it was in the
**              environment.
**
**   -/-i       Start with an empty environment, ignoring the inherited
**        		environment.
**
** Arguments of the form `VARIABLE=VALUE' set the environment variable VARIABLE
** to value VALUE.
**
** VALUE can be empty (`VARIABLE='). Setting a variable to an empty value is
** different from unsetting it.
**
** The first remaining argument specifies the program name to invoke; it is
** searched for according to the `PATH' environment variable. Any remaining
** arguments are passed as arguments to that program.
**
** If no command name is specified following the environment specifications,
** the resulting environment is printed. This is like specifying a command name
** of `printenv'.
*/

static void		sh_env_init_env_before_exec(t_shell *sh, t_env *env)
{
	if (!env_search(env, "PATH") && env->count + 1 < env->size)
		env_insert(sh, env, "PATH", "/usr/bin/:/bin/");
}

static char		sh_env_unset(t_env *env, char *arg)
{
	char	*arg_parsed;

	if (!arg)
		return (sh_env_error(env, NULL, 0, 1));
	if (ft_strcountif(arg, '=') || !env_key_is_ok(arg))
		return (sh_env_error(env, NULL, 0, 2));
	if (!(arg_parsed = sh_parse_quotes(ft_strdups(arg))))
		return (sh_env_error(env, NULL, 0, 3));
	env_delete_item(env, arg_parsed);
	ft_strdel(&arg_parsed);
	return (0);
}

static char		sh_env_options(t_shell *sh, t_env **env, char **argv, int *i)
{
	char	res;

	res = 0;
	while (argv && argv[*i] && argv[*i][0] == '-' && res == 0)
	{
		if (!argv[*i][1] || (argv[*i][1] == 'i' && !argv[*i][2]))
		{
			env_delete(*env);
			*env = env_new(sh, NULL);
		}
		else if (argv[*i][1] == 'u' && !argv[*i][2])
		{
			res = sh_env_unset(*env, argv[*i + 1]);
			*i = *i + 1;
		}
		else if (argv[*i][1] == '-' && !argv[*i][2])
			break ;
		else
			return (sh_env_error(*env, NULL, argv[*i][1], 4));
		if (argv[*i])
			*i = *i + 1;
	}
	return (res);
}

static char		sh_env_add_item_equal(t_shell *sh, t_env *env, char *arg)
{
	int			eq_sym;
	char		*key;
	char		*val;

	key = sh_parse_quotes(ft_strdups(arg));
	eq_sym = sh_get_equal_position(key);
	val = (ft_strchrsp(key, '='))
		? ft_strdups(ft_strchrsp(key, '=')) : ft_strdup("");
	key[eq_sym] = '\0';
	if (!env_key_is_ok(key))
	{
		ft_strdel(&key);
		return (sh_env_error(env, NULL, 0, 2));
	}
	if (!env_search(env, key) && env->count + 1 >= env->size)
	{
		sh_setenv_error(key, val, 4, NULL);
		return (sh_env_error(env, NULL, 0, 0));
	}
	env_insert(sh, env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}

char			sh_env(t_shell *sh, t_env *src, char **argv)
{
	int		i;
	int		res;
	bool	preset;
	t_env	*env;
	t_bin	*bin;

	i = 0;
	preset = FALSE;
	env = env_new(sh, src->environment);
	if ((res = sh_env_options(sh, &env, argv, &i)) != 0)
		return (res);
	while (argv[i] && ft_strcountif(argv[i], '='))
	{
		if (argv[i][0] == '=')
			return (sh_env_error(env, NULL, 0, 5));
		sh_env_add_item_equal(sh, env, argv[i]);
		i++;
	}
	if (!argv[i])
		return (sh_env_print(env));
	preset = (env_search(env, "PATH")) ? FALSE : TRUE;
	(preset) ? sh_env_init_env_before_exec(sh, env) : 0;
	bin = bin_new(sh, env);
	(preset) ? sh_env_unset(env, "PATH") : 0;
	return (sh_env_exec(sh, env, bin, argv + i));
}
