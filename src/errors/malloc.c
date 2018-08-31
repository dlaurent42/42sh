/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:43:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 23:56:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_malloc_shell(t_shell *shell)
{
	if (shell)
		shell_delete(shell);
	ft_putendl_fd("Cannot malloc t_shell structure", 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_env(t_shell *shell, t_env *env, char *name)
{
	if (env)
		env_delete(env);
	if (shell)
		shell_delete(shell);
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_bin(t_shell *shell, t_bin *bin, char *name)
{
	if (bin)
		bin_delete(bin);
	if (shell)
		shell_delete(shell);
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}
