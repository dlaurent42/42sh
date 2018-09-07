/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/07 14:56:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_command_run(t_shell *shell)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	ft_printf("\nNumber of columns: %d\nNumber of lines: %d\n",
	w.ws_col, w.ws_row);
	ft_printf("%s", shell->read->buffer.content);
	ft_putendl("\n---Command sent---");
	shell->term->display_mode = FALSE;
	bzero(shell->read->buffer.content, ARG_MAX);
	ft_memset((void *)shell->read, 0, sizeof(t_read));
	ft_memset((void *)&shell->term->cursor, 0, sizeof(t_cursor));
}
