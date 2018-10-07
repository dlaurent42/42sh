/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:58:26 by dhojt            ###   ########.fr       */
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

static char			*get_auto_mode(t_ac *ac, char *content)
{
	char			*str;
	char			*slash;

	if (!(str = ft_strrchr(move_past_leading_spaces(content), ' ')))
	{
		str = content;
		ac->auto_mode = AUTO_BIN;
		ac->pre_file_name = ft_strnew(0);
	}
	else
	{
		ac->auto_mode = AUTO_REG;
		str++;
		if ((slash = ft_strrchr(str, '/')))
			ac->pre_file_name = ft_strndup(content, (slash - content) + 1);
		else
			ac->pre_file_name = ft_strndup(content, (str - content));
	}
	if (!contains_printable_characters(content) || !ac->pre_file_name)
		return (NULL);
	return (str);
}

static bool			create_ac(t_ac *ac, t_shell *shell, char *str)
{
	ac->shell = shell;
	if (!(ac->argv = (char **)malloc(sizeof(char *) * 3)))
		return (false);
	ac->argv[0] = str;
	ac->argv[1] = str;
	ac->argv[2] = NULL;
	return (true);
}

bool				auto_completion(t_shell *shell)
{
	t_ac			ac;
	bool			performed_completion;
	char			*parsed_buffer;

	performed_completion = false;
	shell->modes.auto_completion = 1;
	if (auto_history(shell))
		performed_completion = true;
	else if (!ft_strcmps(shell->read->line, K_TAB))
	{
		ft_bzero(&ac, sizeof(ac));
		if (!(parsed_buffer = get_auto_mode(&ac, shell->buffer.content)))
			return (false);
		if (create_ac(&ac, shell, parsed_buffer)
				&& auto_get_obj(&ac))
			auto_issuance(&ac);
		auto_free_ac(&ac);
		performed_completion = true;
	}
	shell->modes.auto_completion = 0;
	return (performed_completion);
}
