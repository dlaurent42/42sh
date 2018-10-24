/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:52:08 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/24 14:45:11 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				replace_buffer_content(
		t_shell *sh, char *str, char *glob, char *ptr_to_cont)
{
	char			*track;
	int				number_of_deletions;

	if (!ft_strcmps(str, glob))
		return (false);
	number_of_deletions = ft_strlens(str);
	track = sh->buffer.content + sh->buffer.ushift;
	sh_move_home(sh);
	while (track++ != ptr_to_cont)
		sh_move_right(sh);
	while (number_of_deletions--)
		sh_delete_current_char(sh);
	sh_print_str(sh, glob);
	sh_print_str(sh, " ");
	sh_move_end(sh);
	return (true);
}

bool				auto_glob(t_shell *sh)
{
	bool			status;
	char			*ptr_to_cont;
	char			*str;
	char			*glob;

	str = NULL;
	glob = NULL;
	status = false;
	if (ft_strcmps(sh->read->line, K_TAB))
		return (status);
	if ((ptr_to_cont = ft_strrchr(sh->buffer.content + sh->buffer.ushift, ' ')))
		ptr_to_cont++;
	else
		ptr_to_cont = sh->buffer.content + sh->buffer.ushift;
	str = ft_strdups(ptr_to_cont);
	glob = sh_glob(ft_strdup(str));
	if (str && glob)
		status = replace_buffer_content(sh, str, glob, ptr_to_cont);
	free(str);
	free(glob);
	return (status);
}
