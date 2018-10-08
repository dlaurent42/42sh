/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:17:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:43:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

t_cmd				*get_cmd_by_content(t_shell *sh, char *content)
{
	int				len;
	t_cmd			*cmd;


	len = ft_strlens(content);
	cmd = sh->cmd;
	while (cmd && ft_strncmp(content, cmd->content, len))
		cmd = cmd->next;
	return (cmd);
}

void				auto_hist_name(t_shell *sh, bool *status)
{
	int				number_of_deletions;
	int				offset;
	char			*track;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(sh->buffer.content + offset++, "!")))
	{
		if (!ft_isdigit(*(ptr_to_exc + 1)))
		{
			if ((cmd = get_cmd_by_content(sh, ptr_to_exc + 1)))
			{
				number_of_deletions = ft_strlens(ptr_to_exc);
				track = sh->buffer.content;
				sh_move_home(sh);
				while (track++ != ptr_to_exc)
					sh_move_right(sh);
				while (number_of_deletions--)
					sh_delete_current_char(sh);
				auto_manage_buffer(sh, cmd->content);
				*status = true;
				sh_move_end(sh);
			}
		}
	}
}
