/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_sed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:34:33 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/16 08:48:34 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			do_error(t_shell *sh, bool *status)
{
	if (sh)
		;
	if (*status)
		ft_putendl("ERROR");/////////////////////////////////
	*status = false;
}

static bool			content_is_hist_sed(t_shell *sh, char *content)
{
	int				number_of_chevrons;
	bool			status;
	char			*chevron;

	status = true;
	if (status && (chevron = ft_strrchr(content, '^')) && *(chevron + 1))
		do_error(sh, &status);
	number_of_chevrons = 0;
	while (status && *content && number_of_chevrons < 4)
	{
		if (*content == '^' && *(content + 1) == '^')
			do_error(sh, &status);
		if (*content == '^')
			number_of_chevrons++;
		content++;
	}
	if (number_of_chevrons != 3)
		do_error(sh, &status);
	return (status);
}

char				*content(t_shell *sh)
{
	return (sh->buffer.content + sh->buffer.ushift);
}

char				*get_substitution(t_shell *sh)
{
	char			*needle;

	needle = ft_strchr(content(sh), '^');
	if (needle && *needle)
		needle++;
	if (needle && *needle)
		needle = ft_strchr(needle, '^');
	needle++;
	needle = ft_strndup(needle, ft_strlens(needle) - 1);
	return (needle);
}

char				*get_pointer_to_needle_in_cmd(t_shell *sh)
{
	char			*needle;
	char			*ptr_to_matched_char_in_cmd;

	needle = NULL;
	ptr_to_matched_char_in_cmd = NULL;
	if (sh->cmd && (needle = ft_strndup((content(sh) + 1),
					ft_strchr((content(sh) + 1), '^') - (content(sh) + 1))))
		ptr_to_matched_char_in_cmd = ft_strstr(sh->cmd->content, needle);
	free(needle);
	return (ptr_to_matched_char_in_cmd);
}

void				auto_hist_sed(t_shell *sh, bool *status)//make bool
{
	//int				number_of_deletions;
	//char			*track;
	char			*needle_in_content;
	char			*substitution;

	if (*content(sh) && *content(sh) == '^')
	{
		*status = true;
		if (!content_is_hist_sed(sh, content(sh)))
			return ;
		if (!(needle_in_content = get_pointer_to_needle_in_cmd(sh)))
			return ;
		if (!(substitution = get_substitution(sh)))
			return ;
		ft_putendl(substitution);
		/*
			while ((ptr_to_exc = ft_strstr(sh->buffer.content + sh->buffer.ushift, "!")))
			{
				if (!ft_isdigit(*(ptr_to_exc + 1))
						&& ((cmd = get_cmd_by_content(sh, ptr_to_exc + 1))))
				{
					number_of_deletions = ft_strlens(ptr_to_exc);
					track = sh->buffer.content + sh->buffer.ushift;
					sh_move_home(sh);
					while (track++ != ptr_to_exc)
						sh_move_right(sh);
					while (number_of_deletions--)
						sh_delete_current_char(sh);
					sh_print_str(sh, cmd->content);
					*status = true;
					sh_move_end(sh);
				}
			}
			*/
	}
}
