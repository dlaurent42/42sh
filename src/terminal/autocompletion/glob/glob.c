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

bool				replace_buffer_content(t_shell *shell, char *str, char *glob, char *ptr_to_content)
{
	if (!ft_strcmps(str, glob))
		return (false);
}

bool				auto_glob(t_shell *sh)
{
	bool			status;
	bool			sed_status;
	char			*ptr_to_content;
	char			*str;
	char			*glob;

	str = NULL;
	glob = NULL;
	status = false;
	if(!(ptr_to_content = ft_strrchr(sh->buffer.content + sh->buffer.ushift, ' ')))
		ptr_to_content = sh->buffer.content + sh->buffer.ushift;
	str = ft_strdups(ptr_to_content);
	glob = sh_glob(str);
	if (str && !glob)
		status = replace_buffer_content(sh, str, glob, ptr_to_content);
	free(str);
	free(glob);
	return (status);
}
