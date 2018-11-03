/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:53:51 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 17:31:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_subshell(t_shell *sh, char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		ft_strncpy(sh->buffer.content, argv[i], ARG_MAX);
		sh->buffer.unicode_len = 0;
		sh->buffer.display_len = 0;
		sh->read->line[0] = '\n';
		sh->modes.subshell = TRUE;
		sh_read(sh);
		i++;
	}
	return (
		(sh->env && env_search(sh->env, "?"))
			? ft_atoi(env_search(sh->env, "?"))
			: 1);
}
