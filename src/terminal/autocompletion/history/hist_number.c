/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:16:58 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:23:28 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

t_cmd				*get_cmd_by_id(t_shell *shell, int id)
{
	t_cmd			*cmd;

	if (id < 0 && shell->cmd)
		id += shell->cmd->id + 1;
	if (!shell->cmd
			|| (unsigned)id > shell->cmd->id
			|| (unsigned)id < !shell->cmd->last->id)
		return NULL;
	cmd = shell->cmd;
	while (cmd && (unsigned)id != cmd->id)
		cmd = cmd->next;
	return (cmd);
}

static int			good_number_of_digits(char *str)
{
	int				number_of_digits;
	int				minus;

	minus = 0;
	number_of_digits = 0;
	if (*str == '-')
	{
		str++;
		minus = 1;
	}
	while (ft_isdigit(*(str++)))
		number_of_digits++;
	if (number_of_digits && number_of_digits <= 6)
		return (number_of_digits + minus);
	return (0);
}

void				auto_hist_number(t_shell *shell, bool *status)
{
	int				number_of_deletions;
	int				offset;
	char			*track;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(shell->buffer.content + offset++, "!")))
	{
		if ((number_of_deletions = good_number_of_digits(ptr_to_exc + 1) + 1))
		{
			if((cmd = get_cmd_by_id(shell, ft_atoi(ptr_to_exc + 1))))
			{
				track = shell->buffer.content;
				sh_move_home(shell);
				while (track++ != ptr_to_exc)
					sh_move_right(shell);
				while (number_of_deletions--)
					sh_delete_current_char(shell);
				auto_manage_buffer(shell, cmd->content);
				*status = true;
				sh_move_end(shell);
			}
		}
	}
}
