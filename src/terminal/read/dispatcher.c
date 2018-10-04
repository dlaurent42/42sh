/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:09:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 17:20:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_arrows_dispatcher(t_shell *sh)
{
	char	*s;

	s = sh->read->line;
	ft_putstr(CURSOR_HIDE);
	(!ft_strcmps(s, "\x1b\x5b\x41")) ? sh_browse_prev(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x42")) ? sh_browse_next(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x43")) ? sh_move_right(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x44")) ? sh_move_left(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x46")) ? sh_move_end(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x48")) ? sh_move_home(sh) : 0;
	(!ft_strcmps(s, "\x1b\x1b\x5b\x41")) ? sh_move_up(sh) : 0;
	(!ft_strcmps(s, "\x1b\x1b\x5b\x42")) ? sh_move_down(sh) : 0;
	(!ft_strcmps(s, "\x1b\x1b\x5b\x43")) ? sh_move_next_word(sh) : 0;
	(!ft_strcmps(s, "\x1b\x1b\x5b\x44")) ? sh_move_previous_word(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x43")) ? sh_select_right_char(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x44")) ? sh_select_left_char(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x46")) ? sh_select_end(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x48")) ? sh_select_home(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x41")) ? sh_select_up(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x42")) ? sh_select_down(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x43"))
		? sh_select_right_word(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x44"))
		? sh_select_left_word(sh) : 0;
	ft_putstr(CURSOR_SHOW);
}

void		sh_deletion_dispatcher(t_shell *sh)
{
	ft_putstr(CURSOR_HIDE);
	if (sh->read->line[0] == 1)
		sh_delete_all(sh);
	else if (sh->read->line[0] == 2)
		sh_delete_previous_word(sh);
	else if (sh->read->line[0] == 5)
		sh_delete_to_end(sh);
	else if (sh->read->line[0] == 6)
		sh_delete_next_word(sh);
	else if (sh->read->line[0] == 8)
		sh_delete_from_home(sh);
	else if (sh->read->line[0] == 127)
		sh_delete_char(sh);
	else
		sh_delete_current_char(sh);
	ft_putstr(CURSOR_SHOW);
}

void		sh_read_dispatcher(t_shell *sh)
{
	if (sh->modes.select && !sh_is_select_combination(sh->read->line))
		sh_unselect_delete(sh, (unsigned char)sh->read->line[0]);
	if (sh->modes.browse && !(sh_is_select_combination(sh->read->line)
	|| sh_is_arrow_combination(sh->read->line)))
		sh_browse_freeze(sh);
	if (sh->read->line[0] == 3)
		sh_copy_selection(sh);
	else if (sh->read->line[0] == 22)
		sh_paste_selection(sh);
	else if (sh->read->line[0] == 24)
		sh_cut_selection(sh);
	else if (sh_is_delete_combination(sh->read->line))
		sh_deletion_dispatcher(sh);
	else if (sh->read->line[0] == 27)
		sh_arrows_dispatcher(sh);
	else if (sh->read->line[0] == 9)
		auto_completion(sh);
	else
	{
		ft_putstr(CURSOR_HIDE);
		sh_fill_buffer(sh);
		ft_putstr(CURSOR_SHOW);
	}
}
