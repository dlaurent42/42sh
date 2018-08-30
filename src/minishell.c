/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/30 21:02:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **environ)
{
	t_env		*env;
	t_shell		*shell;

	env = NULL;
	shell = NULL;
	if (argc > 1)
		ft_printf("%s runs without argument.\n", argv[0]);
	shell = shell_new();
	env = env_new(shell);
	shell->env = env;
	env_initialize(shell, env, environ);
	env_delete(env);
	shell_delete(shell);
	return (0);
}
