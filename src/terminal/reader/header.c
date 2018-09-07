/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:09:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/07 12:47:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_print_header(t_shell *shell)
{
	if (shell->read->buffer.unicode_length == 0
	&& shell->term->display_mode == FALSE)
	{
		write(
			1,
			shell->term->header.content,
			shell->term->header.unicode_length);
		write(1, " ", 1);
	}
	shell->term->display_mode = TRUE;
}
