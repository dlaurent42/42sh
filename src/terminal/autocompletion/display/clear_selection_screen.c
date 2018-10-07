/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_selection_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:18:27 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_clear_selection_screen(t_ac *ac)
{
	int				rows;

	rows = ac->number_of_printed_rows;
	ft_putstr(CLEAR_TO_EOL);
	ft_putstr(K_DOWN);
	if (!(ft_putstr_multi(CLEAR_LINE, rows)))
	{
		while (rows--)
			ft_putstr(CLEAR_LINE);
	}
	ft_putstr(K_UP);
}
