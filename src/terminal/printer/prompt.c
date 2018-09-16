/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:09:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/16 16:24:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_print_prompt(t_shell *shell)
{
	if (shell->read->buffer.unicode_length == 0
	&& shell->term->display_mode == FALSE)
	{
		ft_putstr((char *)shell->term->prompt.content);
		if (shell->term->prompt.display_length_mod == 0)
		{
			ft_putstr(K_DOWN);
			ft_putstr(K_COL_0);
		}
	}
	shell->term->display_mode = TRUE;
}
