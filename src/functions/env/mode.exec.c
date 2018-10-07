/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 21:58:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static char	sh_env_exec_free(char *p, char *f, char **arr)
// {
// 	int	i;

// 	i = 0;
// 	ft_strdel(&p);
// 	ft_strdel(&f);
// 	if (arr)
// 	{
// 		while (arr[i])
// 		{
// 			ft_strdel(&arr[i]);
// 			i++;
// 		}
// 		ft_memdel((void **)&arr);
// 	}
// 	return (0);
// }

char		sh_env_exec(t_env *env, char *path, char **arr)
{
	char	*function;
	char	*returned;

	function = (path)
		? ft_strjoinf(path, arr[0], 3)
		: ft_strdups(arr[0]);
	returned = command_execute_fetch(env, function, arr + 1);
	ft_printf(returned);
	env_delete(env);
	//return (sh_env_exec_free(path, function, arr));
	return (0);
}
