/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_question.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:17:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 10:02:13 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_comparisson_string(char *str, char **end_of_string)
{
	char			*track;

	track = str;
	while (*track)
	{
		if (*track == '?' && *(track - 1) != '!')
			break ;
		track++;
	}
	*end_of_string = track;
	return (ft_strndup(str, track - str));
}

static t_cmd		*get_cmd_by_content(t_shell *sh, char *content,
		char **end_of_string)
{
	t_cmd			*cmd;

	cmd = sh->cmd;
	if (!(content = get_comparisson_string(content, end_of_string)))
		return (NULL);
	while (cmd && !ft_strstr(cmd->content, content))
		cmd = cmd->next;
	free(content);
	return (cmd);
}

static void			swap_content(t_shell *sh, char *ptr_to_exc,
		t_cmd *cmd, char *end_of_string)
{
	int				number_of_deletions;
	char			*track;

	number_of_deletions = end_of_string - ptr_to_exc + 1;
	track = sh->buffer.content + sh->buffer.ushift;
	sh_move_home(sh);
	while (track++ != ptr_to_exc)
		sh_move_right(sh);
	while (number_of_deletions--)
		sh_delete_current_char(sh);
	sh_print_str(sh, cmd->content);
	sh_move_end(sh);
}

void				auto_hist_question(t_shell *sh, bool *status)
{
	int				offset;
	char			*ptr_to_exc;
	char			*end_of_string;
	t_cmd			*cmd;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(
	sh->buffer.content + sh->buffer.ushift + offset++, "!?")))
		if (!*(ptr_to_exc + 2))
			return ;
		else if (!ft_isdigit(*(ptr_to_exc + 2))
			&& ((cmd = get_cmd_by_content(sh, ptr_to_exc + 2, &end_of_string))))
		{
			auto_hist_new_prompt(sh, status);
			swap_content(sh, ptr_to_exc, cmd, end_of_string);
		}
}
