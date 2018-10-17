/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_sed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:34:33 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/17 22:00:41 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			do_error(t_shell *sh, bool *status)
{
	if (sh)
		;
	//if (*status)
	//	ft_putendl("ERROR");/////////////////////////////////
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

static void				get_needles(t_shell *sh, char **needle, char **needle_in_content)
{
	*needle = NULL;
	*needle_in_content = NULL;
	if (sh->cmd && (*needle = ft_strndup((content(sh) + 1),
					ft_strchr((content(sh) + 1), '^') - (content(sh) + 1))))
		*needle_in_content = ft_strstr(sh->cmd->content, *needle);
}

void				auto_hist_sed(t_shell *sh, bool *status)//make bool
{
	int				number_of_deletions;
	char			*track;
	char			*needle;//free it
	char			*needle_in_content;
	char			*substitution;

	if (*content(sh) && *content(sh) == '^')
	{
		*status = true;
		if (!content_is_hist_sed(sh, content(sh)))
			return ;
		get_needles(sh, &needle, &needle_in_content);
		if (!needle || !needle_in_content)//free both
			return ;
		if (!(substitution = get_substitution(sh)))
			return ;
		sh_delete_all(sh);
		sh_print_str(sh, sh->cmd->content);
		sh_move_home(sh);
		track = sh->cmd->content;
		while (track++ != needle_in_content)
			sh_move_right(sh);
		number_of_deletions = ft_strlens(needle);
		while (number_of_deletions--)
			sh_delete_current_char(sh);
		sh_print_str(sh, substitution);
		/*
			while ((ptr_to_exc = ft_strstr(sh->buffer.content + sh->buffer.ushift, "!")))
			{
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
