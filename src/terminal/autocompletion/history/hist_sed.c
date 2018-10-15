/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_sed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:34:33 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/15 19:55:48 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_cmd		*get_cmd_by_content(t_shell *sh, char *content)
{
	int				len;
	t_cmd			*cmd;

	len = ft_strlens(content);
	cmd = sh->cmd;
	while (cmd && ft_strncmp(content, cmd->content, len))
		cmd = cmd->next;
	return (cmd);
}

static bool			content_is_hist_sed(char *content)
{
	int				number_of_chevrons;

	number_of_chevrons = 0;
	if (*content && *content != '^')
		return (false);
	while (*content && number_of_chevrons < 3)
	{
		if (*content == '^' && *(content + 1) == '^')
			return (false);
		if (*content == '^')
			number_of_chevrons++;
	}
	return ((number_of_chevrons == 3));
}


void				auto_hist_sed(t_shell *sh, bool *status)
{
	int				number_of_deletions;
	int				offset;
	char			*track;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	offset = 0;
	if (!content_is_hist_sed(sh->buffer.content + sh->buffer.ushift))
		return ;
	while ((ptr_to_exc = ft_strstr(sh->buffer.content + sh->buffer.ushift + offset++, "!")))
	{
		if (!ft_isdigit(*(ptr_to_exc + 1))
				&& ((cmd = get_cmd_by_content(sh, ptr_to_exc + 1))))
		{
			number_of_deletions = ft_strlens(ptr_to_exc);
			track = sh->buffer.content + sh->buffer.ushift;
			sh_move_home(sh);
			while (track++ != ptr_to_exc)
				sh_move_right(sh);
			while (number_of_deletions--)
				sh_delete_current_char(sh);
			sh_print_str(sh, cmd->content);
			*status = true;
			sh_move_end(sh);
		}
	}
}
