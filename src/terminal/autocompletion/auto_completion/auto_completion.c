/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/17 19:58:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_frame		create_frame(t_shell *shell, char *str)
{
	t_frame			frame;

	ft_bzero(&frame, sizeof(frame));
	frame.shell = shell;
	if(!(frame.argv = (char **)malloc(sizeof(char *) * 3)))
		error_exit(&frame, "Malloc Failed");
	frame.argv[0] = str;
	frame.argv[1] = str;
	frame.argv[2] = NULL;
	if (!(frame.malloc_failed = ft_strdup("MALLOC FAIL")))
		error_exit(&frame, "Malloc Failed");
	return (frame);
}

void				auto_completion(t_shell *shell, char *str)
{
	t_frame			frame;

	frame = create_frame(shell, str);
	get_args(&frame);
	issuance(&frame);
	free_frame(&frame);
}
