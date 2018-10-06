/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/06 08:46:53 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			is_auto_history(t_shell *shell)
{
	int				offset;;
	bool			status;
	char			*track;
	char			*ptr_to_exc;

	sh_debug(NULL, "Enter History\n", NULL);//DEBUG
	offset = 0;
	status = false;
	while ((ptr_to_exc = ft_strstr(shell->buffer.content + offset, "!!")))//Deal with !! hist
	{
		track = shell->buffer.content;
		sh_move_home(shell);
		while (track != ptr_to_exc)
		{
			track++;
			sh_move_right(shell);
			sh_debug(NULL, "FIRST\n", shell->buffer.content);//DEBUG
		}
		if (shell->cmd)
		{
			sh_delete_current_char(shell);
			sh_delete_current_char(shell);
			auto_manage_buffer(shell, shell->cmd->content);
			//sh_fill_buffer(shell);
			status = true;
		}
		offset++;
		sh_move_end(shell);
	}
	return (status);
}

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

	shell->modes.auto_completion = 1;
	if (is_auto_history(shell))
		;
	else {
		ft_bzero(&frame, sizeof(frame));
		if (!(parsed_buffer = get_auto_mode(&frame, shell->buffer.content)))
			return ;
		if (create_frame(&frame, shell, parsed_buffer)
				&& auto_get_args(&frame))
			auto_issuance(&frame);
		auto_free_frame(&frame);
	}
	shell->modes.auto_completion = 0;
}
