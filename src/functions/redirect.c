/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/14 21:50:35 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_command_run(t_shell *shell)
{
	shell->term->display_mode = FALSE;
	sh_move_end(shell);
	ft_putchar('\n');
	ft_memset((void *)shell->read, 0, sizeof(t_read));
	ft_memset((void *)&shell->term->cursor, 0, sizeof(t_cursor));
}
