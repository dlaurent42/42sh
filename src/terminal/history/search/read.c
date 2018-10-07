/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:20:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 19:07:38 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_history_search(t_shell *sh)
{
	char	line[LINE_SIZE];

	sh_search_init(sh);
	ft_bzero(line, 8);
	while (TRUE)
	{
		read(0, line, 7);
		if (line[0] == 3 || sh_is_arrow_combination(line)
		|| ft_strcountif(line, '\n'))
			break ;
		sh_history_move_cursor(sh);
		sh_history_bufferize(sh, line);
		sh_history_perform_search(sh);
		sh_history_print_result(sh);
		ft_bzero(line, 8);
	}
	sh_search_freeze(sh);
}
