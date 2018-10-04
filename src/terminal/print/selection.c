/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:47:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 13:00:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_print_before_selection(t_shell *sh)
{
	char	*substr;

	if (!(substr = ft_strsub(
	sh->buffer.content,
	sh->cursor.rel_pos,
	sh->selection.start_rel - sh->cursor.rel_pos)))
		return ;
	ft_putstr(substr);
	ft_strdel(&substr);
}

static void	sh_print_selection(t_shell *sh, int len)
{
	char	*substr;

	if (!(substr = ft_strsub(
	sh->buffer.content,
	sh->selection.start_rel,
	len)))
		return ;
	ft_putstr("\e[7;37;40m");
	ft_putstr(substr);
	ft_putstr("\033[0m");
	ft_strdel(&substr);
}

static void	sh_print_after_selection(t_shell *sh, int len)
{
	ft_putstr(sh->buffer.content
		+ sh->selection.start_rel + len);
	ft_putchar(' ');
};

void		sh_select_print(t_shell *sh)
{
	int	x;
	int	y;
	int	len;

	x = sh->cursor.x;
	y = sh->cursor.y;
	len = sh_get_selection_len(sh);
	sh->modes.select = TRUE;
	sh_move_home(sh);
	ft_putstr(CLEAR_TO_EOL);
	sh_print_before_selection(sh);
	sh_print_selection(sh, len);
	sh_print_after_selection(sh, len);
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod) / sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh_move_to_xy(sh, x, y);
}
