/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:00:52 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/26 13:01:18 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_env_var(t_shell *sh, char *ptr_to_dollar, int len)
{
	char			**environment;
	char			*env;
	int				total;

	total = 0;
	env = NULL;
	environment = sh->env->environment;
	while (*environment)
	{
		if (!ft_strncmp(*environment, ptr_to_dollar + 1, len - 1))
		{
			env = *environment;
			if (++total > 1)
				return (NULL);
		}
		environment++;
	}
	return (env);
}

bool				auto_env(t_shell *sh)
{
	int				len;
	char			*env;
	char			*track;
	char			*ptr_dollar;

	if ((ptr_dollar = ft_strrchr(sh->buffer.content + sh->buffer.ushift, ' ')))
		ptr_dollar++;
	else
		ptr_dollar = sh->buffer.content + sh->buffer.ushift;
	if (*ptr_dollar != '$')
		return (false);
	len = ft_strlen(ptr_dollar + 1) + 1;
	if (!(env = get_env_var(sh, ptr_dollar, len)) || !ft_strchr(env, '=')
			|| ft_strncmp(env, ptr_dollar + 1, ft_strchr(env, '=') - env)
			|| !(env = ft_strchr(env, '=') + 1))
		return (false);
	track = sh->buffer.content + sh->buffer.ushift;
	sh_move_home(sh);
	while (track++ != ptr_dollar)
		sh_move_right(sh);
	while (len--)
		sh_delete_current_char(sh);
	sh_print_str(sh, env);
	sh_move_end(sh);
	return (true);
}
