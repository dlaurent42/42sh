/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 13:01:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_arrows_dispatcher(t_shell *sh)
{
	char	*s;

	s = sh->read->line;
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
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x43")) ? sh_select_right_word(sh) : 0;
	(!ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x44")) ? sh_select_left_word(sh) : 0;

}

static char	sh_is_select_combination(char *s)
{
	if (s[0] == 3 || s[0] == 22 || s[0] == 24
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x43") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x44") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x46") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x48") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x41") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x42") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x43") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x44") == 0)
		return (TRUE);
	return (FALSE);
}

static void	sh_read_dispatcher(t_shell *sh)
{
	sh_debug(sh, "before", sh->read->line);
	if (sh->modes.select && !sh_is_select_combination(sh->read->line))
		sh_unselect_delete(sh, (unsigned char)sh->read->line[0]);
	if (sh->read->line[0] == 3)
		sh_copy_selection(sh);
	else if (sh->read->line[0] == 22)
		sh_paste_selection(sh);
	else if (sh->read->line[0] == 24)
		sh_cut_selection(sh);
	else if (sh->read->line[0] == 27)
		sh_arrows_dispatcher(sh);
	else if (sh->read->line[0] == 127)
		sh_read_delete(sh);
	else if (sh->read->line[0] == 9)
		sh_read_autocompletion(sh);
	else
		sh_fill_buffer(sh);
}

void		sh_read(t_shell *sh)
{
	while (TRUE)
	{
		(sh->modes.display) ? 0 : sh_print_prompt(sh);
		read(0, sh->read->line, 7);
		if (sh->read->line[0] == 4)
			break ;
		sh_read_dispatcher(sh);
		bzero(sh->read->line, 8);
	}
}
