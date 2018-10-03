/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 10:07:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_env_exec_free(char *p, char *s, char *f, char **strsplt)
{
	int	i;

	i = 0;
	ft_strdel(&p);
	ft_strdel(&s);
	ft_strdel(&f);
	if (strsplt)
	{
		while (strsplt[i])
		{
			ft_strdel(&strsplt[i]);
			i++;
		}
		ft_memdel((void **)&strsplt);
	}
	return (0);
}

char		sh_env_exec(t_env *env, char *path, char *string)
{
	char	*function;
	char	*returned;
	char	**strsplt;

	strsplt = ft_strsplit(string, ' ');
	function = (path)
		? ft_strjoinf(path, strsplt[0], 3)
		: ft_strdups(strsplt[0]);
	returned = command_execute_fetch(env, function, strsplt + 1);
	ft_printf(returned);
	env_delete(env);
	return (sh_env_exec_free(path, string, function, strsplt));
}
