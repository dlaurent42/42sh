/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:52:08 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/23 00:02:03 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				replace_buffer_content(t_shell *sh, char *str, char *glob, char *ptr_to_content)
{
	char			*content;
	int				number_of_deletions;

	if (!ft_strcmps(str, glob))
		return (false);
	number_of_deletions = ft_strlens(glob);
	content = sh->buffer.content + sh->buffer.ushift;
	sh_move_home(sh);
	while (content++ != ptr_to_content)
		sh_move_right(sh);
	while (number_of_deletions--)
		sh_delete_current_char(sh);
	sh_print_str(sh, glob);
	return (true);
}

bool				auto_glob(t_shell *sh)
{
	bool			status;
	char			*ptr_to_content;
	char			*str;
	char			*glob;

	str = NULL;
	glob = NULL;
	status = false;
	if (ft_strcmps(sh->read->line, K_TAB))
		return (false);
	if(!(ptr_to_content = ft_strrchr(sh->buffer.content + sh->buffer.ushift, ' ')))
		ptr_to_content = sh->buffer.content + sh->buffer.ushift;
	str = ft_strdups(ptr_to_content);
	glob = sh_glob(ft_strdup(str));
	if (str && glob)
		status = replace_buffer_content(sh, str, glob, ptr_to_content);
	free(str);
	free(glob);
	return (status);
}
