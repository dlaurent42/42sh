/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:09:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 13:53:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_print_header(t_shell *shell)
{
	if (shell->read->buffer.unicode_length == 0
	&& shell->term->display_mode == FALSE)
	{
		ft_printf("\e[1;32;40m%s\033[0m ", shell->term->header.content);
		if (shell->term->header.display_length_mod == 0)
		{
			ft_putstr(K_DOWN);
			ft_putstr(K_COL_0);
		}
	}
	shell->term->display_mode = TRUE;
}
