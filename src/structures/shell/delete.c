/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:13:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 16:27:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_delete(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		env_delete(shell->env);
	if (shell->bin)
		bin_delete(shell->bin);
	if (shell->term)
		term_delete(shell->term);
	free(shell);
}
