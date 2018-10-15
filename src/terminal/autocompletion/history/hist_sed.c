/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_sed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:34:33 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/15 20:35:03 by dhojt            ###   ########.fr       */
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

static void			do_error(t_shell *sh, bool *status)
{
	if (sh)
		;
	*status = false;
	ft_putendl("ERROR");/////////////////////////////////
}

static bool			content_is_hist_sed(t_shell *sh, char *content)
{
	int				number_of_chevrons;
	bool			status;
	char			*chevron;

	status = true;
	if (*content && *content == '^')
	{
		if (status && (chevron = ft_strrchr(content, '^')) && *(chevron + 1))
			do_error(sh, &status);
		number_of_chevrons = 0;
		while (status && *content && number_of_chevrons < 4)
		{
			if (*content == '^' && *(content + 1) == '^')
				do_error(sh, &status);
			if (*content == '^')
				number_of_chevrons++;
			content++;
		}
		if (number_of_chevrons != 3)
			do_error(sh, &status);
	}
	return (status);
}

void				auto_hist_sed(t_shell *sh, bool *status)
{
	int				number_of_deletions;
	char			*track;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	if (!content_is_hist_sed(sh, sh->buffer.content + sh->buffer.ushift))
		return ;
	while ((ptr_to_exc = ft_strstr(sh->buffer.content + sh->buffer.ushift, "!")))
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
