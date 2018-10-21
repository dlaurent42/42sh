/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:16:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/21 17:08:10 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd				*get_cmd_by_id(t_shell *sh, int id)
{
	t_cmd			*cmd;

	if (id < 0 && sh->cmd)
		id += sh->cmd->id + 1;
	if (!sh->cmd
			|| (unsigned)id > sh->cmd->id
			|| (unsigned)id < !sh->cmd->last->id)
		return (NULL);
	cmd = sh->cmd;
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

void				auto_hist_number(t_shell *sh, bool *status)
{
	int				number_of_deletions;
	int				offset;
	char			*track;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(
			sh->buffer.content + sh->buffer.ushift + offset++,
			"!")))
		if ((number_of_deletions = good_number_of_digits(ptr_to_exc + 1) + 1))
			if ((cmd = get_cmd_by_id(sh, ft_atoi(ptr_to_exc + 1))))
			{
				auto_hist_new_prompt(sh, status);
				track = sh->buffer.content + sh->buffer.ushift;
				sh_move_home(sh);
				while (track++ != ptr_to_exc)
					sh_move_right(sh);
				while (number_of_deletions--)
					sh_delete_current_char(sh);
				sh_print_str(sh, cmd->content);
				sh_move_end(sh);
			}
}
