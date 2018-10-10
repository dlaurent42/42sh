/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/10 20:43:08 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

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
		if (ft_isprint(*str))
			return (true);
		str++;
	}
	return (false);
}

static char			*get_auto_mode(t_shell *sh, char *content)
{
	char			*str;
	char			*slash;

	if (!(str = ft_strrchr(move_past_leading_spaces(content), ' ')))
	{
		str = content;
		sh->ac->auto_mode = AUTO_BIN;
		sh->ac->pre_file_name = ft_strnew(0);
	}
	else
	{
		sh->ac->auto_mode = AUTO_REG;
		str++;
		if ((slash = ft_strrchr(str, '/')))
			sh->ac->pre_file_name = ft_strndup(content, (slash - content) + 1);
		else
			sh->ac->pre_file_name = ft_strndup(content, (str - content));
	}
	if (!contains_printable_characters(content) || !sh->ac->pre_file_name)
		return (NULL);
	return (str);
}

static bool			create_ac(t_shell *sh, char *str)
{
	if (!(sh->ac->argv = (char **)malloc(sizeof(char *) * 3)))
		return (false);
	sh->ac->argv[0] = str;
	sh->ac->argv[1] = str;
	sh->ac->argv[2] = NULL;
	return (true);
}

bool				auto_completion(t_shell *sh)
{
	bool			performed_completion;
	char			*parsed_buffer;

	performed_completion = false;
	sh->modes.auto_completion = 1;
	if (auto_history(sh))
		performed_completion = true;
	else if (!ft_strcmps(sh->read->line, K_TAB))
	{
		if (!(sh->ac = (t_ac *)malloc(sizeof(t_ac))))
			return (false);
		ft_bzero(sh->ac, sizeof(t_ac));
		if (!(parsed_buffer = get_auto_mode(sh, sh->buffer.content)))
			return (false);
		if (create_ac(sh, parsed_buffer)
				&& auto_get_obj(sh))
			auto_issuance(sh);
		auto_free_ac(sh);
		performed_completion = true;
	}
	sh->modes.auto_completion = 0;
	return (performed_completion);
}
