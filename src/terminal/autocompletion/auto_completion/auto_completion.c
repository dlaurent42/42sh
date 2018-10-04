/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/04 19:10:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*move_past_leading_spaces(char *content)
{
	while (content && *content == ' ')
		content++;
	return (content);
}

static bool			contains_printable_characters(char *str)
{
	while (str && *str)
	{
		if (ft_isalnum(*str))
			return (true);
		str++;
	}
	return (false);
}

static char			*get_auto_mode(t_frame *frame, char *content)
{
	char			*str;
	char			*slash;

	if (!(str = ft_strrchr(move_past_leading_spaces(content), ' ')))
	{
		str = content;
		frame->auto_mode = AUTO_BIN;
		frame->pre_file_name = ft_strnew(0);
	}
	else
	{
		frame->auto_mode = AUTO_REG;
		str++;
		if ((slash = ft_strrchr(str, '/')))
			frame->pre_file_name = ft_strndup(content, (slash - content) + 1);
		else
			frame->pre_file_name = ft_strndup(content, (str - content));
	}
	if (!contains_printable_characters(content) || !frame->pre_file_name)
		return (NULL);
	return (str);
}

static bool			create_frame(t_frame *frame, t_shell *shell, char *str)
{
	frame->shell = shell;
	if (!(frame->argv = (char **)malloc(sizeof(char *) * 3)))
		return (false);
	frame->argv[0] = str;
	frame->argv[1] = str;
	frame->argv[2] = NULL;
	return (true);
}

void				auto_completion(t_shell *shell)
{
	t_frame			frame;
	char			*parsed_buffer;

	if (shell->modes.multiline)
		return ;
	ft_bzero(&frame, sizeof(frame));
	shell->modes.auto_completion = 1;
	if (!(parsed_buffer = get_auto_mode(&frame, shell->buffer.content)))
		return ;
	if (create_frame(&frame, shell, parsed_buffer)
			&& auto_get_args(&frame))
		auto_issuance(&frame);
	auto_free_frame(&frame);
	shell->modes.auto_completion = 0;
}
