/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/09/24 00:20:16 by dhojt            ###   ########.fr       */
=======
/*   Updated: 2018/09/23 17:28:20 by dhojt            ###   ########.fr       */
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
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
<<<<<<< HEAD
	frame = create_frame(frame, shell, get_string(&frame, shell->buffer.content));
=======
	frame = create_frame(frame, shell, get_string(&frame, shell->read->buffer.content));
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
	get_args(&frame);
	issuance(&frame);
	free_frame(&frame);
}
