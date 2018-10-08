/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 07:04:15 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"
# include "auto_completion_prot.h"

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

static char			*get_auto_mode(t_shell *shell, char *content)
{
	char			*str;
	char			*slash;

	if (!(str = ft_strrchr(move_past_leading_spaces(content), ' ')))
	{
		str = content;
		shell->ac->auto_mode = AUTO_BIN;
		shell->ac->pre_file_name = ft_strnew(0);
	}
	else
	{
		shell->ac->auto_mode = AUTO_REG;
		str++;
		if ((slash = ft_strrchr(str, '/')))
			shell->ac->pre_file_name = ft_strndup(content, (slash - content) + 1);
		else
			shell->ac->pre_file_name = ft_strndup(content, (str - content));
	}
	if (!contains_printable_characters(content) || !shell->ac->pre_file_name)
		return (NULL);
	return (str);
}

static bool			create_ac(t_shell *shell, char *str)
{
	if (!(shell->ac->argv = (char **)malloc(sizeof(char *) * 3)))
		return (false);
	shell->ac->argv[0] = str;
	shell->ac->argv[1] = str;
	shell->ac->argv[2] = NULL;
	return (true);
}

bool				auto_completion(t_shell *shell)
{
	bool			performed_completion;
	char			*parsed_buffer;

	performed_completion = false;
	shell->modes.auto_completion = 1;
	if (auto_history(shell))
		performed_completion = true;
	else if (!ft_strcmps(shell->read->line, K_TAB))
	{
		if (!(shell->ac = (t_ac *)malloc(sizeof(t_ac))))
			return (false);
		ft_bzero(shell->ac, sizeof(t_ac));
		if (!(parsed_buffer = get_auto_mode(shell, shell->buffer.content)))
			return (false);
		if (create_ac(shell, parsed_buffer)
				&& auto_get_obj(shell))
			auto_issuance(shell);
		auto_free_ac(shell);//FREE IT PROPERLY ONCE WORKING
		performed_completion = true;
	}
	shell->modes.auto_completion = 0;
	return (performed_completion);
}
