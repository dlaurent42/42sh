/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 10:53:16 by dlaurent         ###   ########.fr       */
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

static void	sh_env_exec_verbose(char *path, char **arr)
{
	int	i;

	i = 1;
	ft_putstr("#env executing: ");
	ft_putendl(path);
	ft_putstr("#env    arg[0]= 'ls'");
	ft_putendl(path);
	while (arr[i])
	{
		ft_printf("#env    arg[%d]= '%s'\n", i, arr[i]);
		i++;
	}
}

char		sh_env_exec(t_env *env, char *path, char **arr, bool verbose)
{
	char	*function;
	char	*returned;

	function = (path)
		? ft_strjoinf(path, arr[0], 2)
		: ft_strdups(arr[0]);
	if (verbose)
		sh_env_exec_verbose(path, arr);
	returned = command_execute_fetch(env, function, arr + 1);
	ft_printf(returned);
	env_delete(env);
	//return (sh_env_exec_free(path, function, arr));
	return (0);
}
