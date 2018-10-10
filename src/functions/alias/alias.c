/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:42:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 16:45:35 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_alias(t_shell *sh, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	if (argc == 0)
		return (sh_alias_error(NULL, NULL, 1));
	while (argv[i] && (res = sh_alias_add(sh, sh->local_env, argv[i])) == 0)
		i++;
	return (res);
}
