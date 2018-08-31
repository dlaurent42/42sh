/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 23:48:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **environ)
{
	t_env		*env;
	t_shell		*shell;

	env = NULL;
	shell = NULL;
	(void)argc;
	(void)argv;
	shell = shell_new();
	shell->env = env_new(shell, environ);
	shell->bin = bin_new(shell);
	shell_delete(shell);
	return (0);
}
