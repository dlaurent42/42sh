/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:09:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/08 16:18:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_arrows_dispatcher(t_shell *sh)
{
	char	*s;

	s = sh->read->line;
	ft_putstr(CURSOR_HIDE);
	(!ft_strcmps(s, K_UP)) ? sh_browse_prev(sh) : 0;
	(!ft_strcmps(s, K_DOWN)) ? sh_browse_next(sh) : 0;
	(!ft_strcmps(s, K_RIGHT)) ? sh_move_right(sh) : 0;
	(!ft_strcmps(s, K_LEFT)) ? sh_move_left(sh) : 0;
	(!ft_strcmps(s, K_END)) ? sh_move_end(sh) : 0;
	(!ft_strcmps(s, K_HOME)) ? sh_move_home(sh) : 0;
	(!ft_strcmps(s, K_O_UP)) ? sh_move_up(sh) : 0;
	(!ft_strcmps(s, K_O_DOWN)) ? sh_move_down(sh) : 0;
	(!ft_strcmps(s, K_O_RIGHT)) ? sh_move_next_word(sh) : 0;
	(!ft_strcmps(s, K_O_LEFT)) ? sh_move_previous_word(sh) : 0;
	(!ft_strcmps(s, K_S_RIGHT)) ? sh_select_right_char(sh) : 0;
	(!ft_strcmps(s, K_S_LEFT)) ? sh_select_left_char(sh) : 0;
	(!ft_strcmps(s, K_S_END)) ? sh_select_end(sh) : 0;
	(!ft_strcmps(s, K_S_HOME)) ? sh_select_home(sh) : 0;
	(!ft_strcmps(s, K_S_O_UP)) ? sh_select_up(sh) : 0;
	(!ft_strcmps(s, K_S_O_DOWN)) ? sh_select_down(sh) : 0;
	(!ft_strcmps(s, K_S_O_RIGHT)) ? sh_select_right_word(sh) : 0;
	(!ft_strcmps(s, K_S_O_LEFT)) ? sh_select_left_word(sh) : 0;
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
	if (sh->read->line[0] == 11)
		sh_copy_selection(sh);
	else if (sh->read->line[0] == 16)
		sh_paste_selection(sh);
	else if (sh->read->line[0] == 24)
		sh_cut_selection(sh);
	else if (sh_is_delete_combination(sh->read->line))
		sh_deletion_dispatcher(sh);
	else if (sh->read->line[0] == 27)
		sh_arrows_dispatcher(sh);
	else if (sh->read->line[0] == 18)
		sh_history_search(sh);
	else if (sh->read->line[0] == 9)
		auto_completion(sh);
	else if (sh->read->line[0])
		sh_fill_buffer(sh);
}
