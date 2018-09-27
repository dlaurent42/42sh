/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/27 12:20:57 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_string(t_frame *frame, char *content)
{
	char			*str;
	ft_printf("GETTING: %s\n", content);

	if (!(str = ft_strrchr(content, ' ')))
	{
		str = content;
		frame->auto_mode = AUTO_BIN;
	}
	else
	{
		str++;
		frame->auto_mode = AUTO_REG;
	}
	ft_printf("Mode is %d\n", frame->auto_mode);
	return (str);
}

static t_frame		create_frame(t_frame frame, t_shell *shell, char *str)
{
	frame.shell = shell;
	if(!(frame.argv = (char **)malloc(sizeof(char *) * 3)))
		error_exit(&frame, "Malloc Failed");
	ft_printf("GOT: [%s]\n", str);
	frame.argv[0] = str;
	frame.argv[1] = str;
	frame.argv[2] = NULL;
	if (!(frame.malloc_failed = ft_strdup("MALLOC FAIL")))
		error_exit(&frame, "Malloc Failed");
	return (frame);
}

void				auto_completion(t_shell *shell)
{
	t_frame			frame;

	ft_bzero(&frame, sizeof(frame));
	sh_replace_buffer(shell, "ls ");//Sample initial buffer content.
	frame = create_frame(frame, shell, get_string(&frame, shell->buffer.content));
	get_args(&frame);
	issuance(&frame);
	free_frame(&frame);
}
