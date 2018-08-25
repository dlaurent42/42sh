/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:45:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 18:58:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment_init(t_shell *shell, t_env **env, char **environ)
{
	int		i;

	i = 0;
	while (env[i])
	{
		environment_add(shell, env, environ);
		i++;
	}
	if (*env)
		shell->env = (*env)->head;
}
