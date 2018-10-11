/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.prepare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 22:51:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 23:02:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_env_prepare_u(int *j, int *i, char **argv)
{
	int	k;

	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		*j = ft_strlens(argv[*i]) - 1;
		if (argv[*i])
			return (argv[*i]);
		return (NULL);
	}
	*j = ft_strlens(argv[*i]) - 1;
	return (argv[*i] + k);
}

char	sh_env_prepare_s(char **string, int *j, int *i, char **argv)
{
	int	k;

	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		*j = ft_strlens(argv[*i]) - 1;
		if (argv[*i])
			return (sh_env_string(argv[*i], string));
		return (-4);
	}
	*j = ft_strlens(argv[*i]) - 1;
	return (sh_env_string(argv[*i] + k, string));
}

char	sh_env_prepare_p(char **path, int *j, int *i, char **argv)
{
	int	k;

	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		*j = ft_strlens(argv[*i]) - 1;
		if (argv[*i])
			return (sh_env_path(argv[*i], path));
		return (-3);
	}
	*j = ft_strlens(argv[*i]) - 1;
	return (sh_env_path(argv[*i] + k, path));
}
