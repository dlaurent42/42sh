/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:17:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/23 11:15:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_hist_double(t_shell *sh, bool *status)
{
	int				i;
	int				offset;
	char			*track;
	char			*ptr_to_exc;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(
					sh->buffer.content + sh->buffer.ushift + offset++,
					"!!")) && sh->cmd)
	{
		auto_hist_new_prompt(sh, status);
		track = sh->buffer.content + sh->buffer.ushift;
		sh_move_home(sh);
		while (track++ != ptr_to_exc)
			sh_move_right(sh);
		sh_delete_current_char(sh);
		sh_delete_current_char(sh);
		i = 0;
		while (sh->cmd->content[i])
		{
			ft_bzero(sh->read->line, LINE_SIZE);
			sh->read->line[0] = sh->cmd->content[i];
			sh_fill_buffer(sh);
			i++;
		}
		ft_bzero(sh->read->line, LINE_SIZE);
		sh_move_end(sh);
	}
}
