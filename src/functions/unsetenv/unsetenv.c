/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/01 14:39:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unsetenv(t_shell *sh, char *args)
{
	if (!env_search(sh->env, args))
		return (-1);
	env_delete_item(sh->env, args);
	if (env_search(sh->env, args))
		return (-1);
	return (0);
}
