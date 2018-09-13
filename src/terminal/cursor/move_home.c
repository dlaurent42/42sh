/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_home.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/13 17:01:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_home(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	ft_putstr(K_HOME);
	while (i < shell->term->header.display_length_mod + 1)
	{
		ft_putstr(K_RIGHT);
		i++;
	}
	shell->term->cursor.x = 0;
	shell->term->cursor.y = 0;
	shell->term->cursor.abs_pos = 0;
	shell->term->cursor.rel_pos = 0;
}
