/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/26 21:34:02 by dlaurent         ###   ########.fr       */
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
	shell_init(&shell);
	environment_init(shell, &env, environ);
	free_shell(shell, TRUE);
	return (0);
}
