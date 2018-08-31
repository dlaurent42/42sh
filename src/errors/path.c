/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:55:49 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 00:57:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_no_path_var(t_shell *shell)
{
	if (shell)
		shell_delete(shell);
	ft_putendl_fd("PATH variable is unset", 2);
	exit(EXIT_FAILURE);
}
