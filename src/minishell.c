/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/17 21:44:13 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **environ)
{
	t_shell		*shell;

	shell = NULL;
	(void)argc;
	(void)argv;
	shell = shell_new();
	shell->env = env_new(shell, environ);
	shell->bin = bin_new(shell);
	shell->read = read_new(shell);
	shell->term = term_new(shell);
	signal_catching();
	auto_completion(shell, "");
	sh_read(shell);
	shell_delete(shell);
	return (0);
}
