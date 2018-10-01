/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/01 16:01:10 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	OPTIONS
**		option -L : Force symbolic links to be followed (default behavior)
**		option -P : Use the physical directory structure without following
**					symbolic links
**
**	EXAMPLES
**		cd link -> repo => link
**		cd -L link -> repo => link
**		cd -P link -> repo => repo
**		cd -L -P link -> repo => repo
**
**	ERRORS
**		if link name equal to itself -> too many levels of symbolic links
**		if link/repo does not exist -> no such file or directory
*/

static void	sh_cd_del_args(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i])
	{
		ft_strdel(&args[i]);
		i++;
	}
	free(args);
}

static char	sh_cd_dispatch(t_shell *sh, int option_p, char **args, int current)
{
	if (!args[current])
		return (sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL));
	if (args[current] && args[current + 1])
		return (sh_cd_error(args[current], NULL, 4));
	if (args[current][0] == '-' && args[current][1] == '-' && !args[current][2])
		return (sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL));
	if (option_p && args[current][0] == '-' && !args[current][1])
		return (sh_cd_nofollow(sh, env_search(sh->env, "OLDPWD"), NULL));
	if (option_p)
		return (sh_cd_nofollow(sh, args[current], NULL));
	if (args[current][0] == '-' && !args[current][1])
		return (sh_cd_follow(sh, env_search(sh->env, "OLDPWD")));
	return (sh_cd_follow(sh, args[current]));
}

char		sh_cd(t_shell *sh, char *command)
{
	char	result;
	char	**args;
	int		current;
	int		option_p;
	int		option_l;

	current = 0;
	option_l = 0;
	option_p = 0;
	if (!command || !(args = ft_strsplit(command, ' ')))
		return (-1);
	while (args[current] && args[current][0] == '-')
	{
		if (args[current][1] == 'L' && !args[current][2])
			option_l = TRUE;
		else if (args[current][1] == 'P' && !args[current][2])
			option_p = TRUE;
		else
			break ;
		current++;
	}
	result = sh_cd_dispatch(sh, option_p, args, current);
	sh_cd_del_args(args);
	return (result);
}
