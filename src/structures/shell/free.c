/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:13:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 19:15:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int full_free)
{
	if (!shell)
		return ;
	if (full_free && shell->env)
		free_environment(shell->env);
	free(shell);
}
