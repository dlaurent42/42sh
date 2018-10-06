/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 09:05:58 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/06 09:11:11 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			exc_double(t_shell *shell, bool *status)
{
	int				offset;;
	char			*track;
	char			*ptr_to_exc;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(shell->buffer.content + offset, "!!")))
	{
		track = shell->buffer.content;
		sh_move_home(shell);
		while (track != ptr_to_exc)
		{
			track++;
			sh_move_right(shell);
		}
		if (shell->cmd)
		{
			sh_delete_current_char(shell);
			sh_delete_current_char(shell);
			auto_manage_buffer(shell, shell->cmd->content);
			*status = true;
		}
		offset++;
		sh_move_end(shell);
	}
}

static void			exc_number(t_shell *shell, bool *status)
{
	(void)shell;
	(void)status;
}

bool				auto_history(t_shell *shell)
{
	bool			status;

	status = false;
	exc_double(shell, &status);
	exc_number(shell, &status);
	return (status);
}
