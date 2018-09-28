/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 17:32:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_cd(t_shell *sh, char *path)
{
	int		res;
	char	real_path[PATH_MAX + 1];

	if (!path)
		return (-1);
	if (path[0] == '/')
		ft_strcpy(real_path, path);
	else if (path[0] == '\0')
		(env_search(sh->env, "HOME"))
			? ft_strcpy(real_path, env_search(sh->env, "HOME"))
			: 0;
	else
	{
		ft_strcpy(real_path, sh->prompt.location);
		ft_strcat(real_path, "/");
		ft_strcat(real_path, path);
	}
	if ((res = chdir(real_path)) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(real_path, 2);
	}
	return (res);
}
