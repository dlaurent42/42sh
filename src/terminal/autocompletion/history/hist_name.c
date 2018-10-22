/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:17:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 17:00:08 by dlaurent         ###   ########.fr       */
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

void				swap_content(t_shell *sh, char *ptr_to_exc, t_cmd *cmd)
{
	int				number_of_deletions;
	char			*track;

	number_of_deletions = ft_strlens(ptr_to_exc);
	track = sh->buffer.content + sh->buffer.ushift;
	sh_move_home(sh);
	while (track++ != ptr_to_exc)
		sh_move_right(sh);
	while (number_of_deletions--)
		sh_delete_current_char(sh);
	sh_print_str(sh, cmd->content);
	sh_move_end(sh);
}

void				auto_hist_name(t_shell *sh, bool *status)
{
	int				offset;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(
	sh->buffer.content + sh->buffer.ushift + offset++, "!")))
		if (!*(ptr_to_exc + 1))
			return ;
		else if (!ft_isdigit(*(ptr_to_exc + 1))
				&& ((cmd = get_cmd_by_content(sh, ptr_to_exc + 1))))
		{
			auto_hist_new_prompt(sh, status);
			swap_content(sh, ptr_to_exc, cmd);
		}
}
