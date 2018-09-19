/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:32:15 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/17 08:43:49 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				loop_dirs(t_frame *frame)
{
	t_args			*args;

	args = frame->args;
	while (args)
	{
		if (args->data.dir && !args->data.no_file)
			do_ls(frame, args);
		args = args->next;
	}
}
