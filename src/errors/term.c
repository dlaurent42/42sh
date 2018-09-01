/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:56:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 02:56:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_no_term_var(t_shell *shell)
{
	if (shell)
		shell_delete(shell);
	ft_putendl_fd("TERM variable is unset", 2);
	exit(EXIT_FAILURE);
}
