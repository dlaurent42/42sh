/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_sed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:34:33 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/21 18:35:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			content_is_hist_sed(char *content)
{
	int				number_of_chevrons;
	bool			is_sed;
	char			*chevron;

	is_sed = true;
	if (is_sed && (chevron = ft_strrchr(content, '^')) && *(chevron + 1))
		is_sed = false;
	number_of_chevrons = 0;
	while (is_sed && *content && number_of_chevrons < 4)
	{
		if (*content == '^' && *(content + 1) == '^')
			is_sed = false;
		if (*content == '^')
			number_of_chevrons++;
		content++;
	}
	if (number_of_chevrons != 3)
		is_sed = false;
	return (is_sed);
}

static char			*get_substitution(t_shell *sh)
{
	char			*needle;
	char			*content;

	content = sh->buffer.content + sh->buffer.ushift;
	needle = ft_strchr(content, '^');
	if (needle && *needle)
		needle++;
	if (needle && *needle)
		needle = ft_strchr(needle, '^');
	needle++;
	needle = ft_strndup(needle, ft_strlens(needle) - 1);
	return (needle);
}

static void			get_needles(t_shell *sh, char **needle,
		char **needle_in_content)
{
	char			*content;

	content = sh->buffer.content + sh->buffer.ushift;
	*needle = NULL;
	*needle_in_content = NULL;
	if (sh->cmd && (*needle = ft_strndup((content + 1),
					ft_strchr((content + 1), '^') - (content + 1))))
		*needle_in_content = ft_strstr(sh->cmd->content, *needle);
}

/*
** strings[0] == needle
** strings[1] == needle_in_content
** strings[3] == substitution
*/

static void			exchange_cmd(t_shell *sh, char **strings, bool *status)
{
	char			*track;
	int				number_of_deletions;

	auto_hist_new_prompt(sh, status);
	sh_delete_all(sh);
	sh_print_str(sh, sh->cmd->content);
	sh_move_home(sh);
	track = sh->cmd->content;
	while (track++ != strings[1])
		sh_move_right(sh);
	number_of_deletions = ft_strlens(strings[0]);
	while (number_of_deletions--)
		sh_delete_current_char(sh);
	sh_print_str(sh, strings[2]);
	sh_move_end(sh);
}

bool				auto_hist_sed(t_shell *sh, bool *status)
{
	char			**strs;
	char			*content;
	bool			success;

	success = false;
	content = sh->buffer.content + sh->buffer.ushift;
	if (*content && *content == '^')
	{
		if (!content_is_hist_sed(content) && (*status = true))
			return (success);
		if (!(strs = (char **)malloc(sizeof(char *) * 3))
				&& (*status = true))
			return (success);
		get_needles(sh, &strs[0], &strs[1]);
		strs[2] = get_substitution(sh);
		if (strs[0] && strs[1] && strs[2] && (success = true))
			exchange_cmd(sh, strs, status);
		else
			*status = true;
		free(strs[0]);
		free(strs[2]);
		free(strs);
	}
	return (success);
}
