/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:43:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 19:13:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_malloc(t_shell *shell, t_env *env, char *name)
{
	if (shell)
		free_shell(shell, FALSE);
	if (env)
		free_environment(env);
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(" structure.", 2);
	exit(EXIT_FAILURE);
}
