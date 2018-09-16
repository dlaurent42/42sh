/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 20:21:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/16 15:56:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_set_prompt_properties(t_term *term, unsigned char has_git)
{
	unsigned char	i;

	i = 0;
	term->prompt.display_length = 0;
	while (term->prompt.content[i])
	{
		if (term->prompt.content[i] >= 0b11000000
		|| term->prompt.content[i] < 0b10000000)
			term->prompt.display_length++;
		i++;
	}
	term->prompt.display_length -= (has_git) ? 54 : 24;
	term->prompt.display_length_mod = term->prompt.display_length % term->window.width;
}

void		term_set_prompt(t_shell *shell, t_term *term)
{
	char	*git;
	size_t	length;

	git = NULL;
	(term->prompt.content) ? ft_strdel((char **)&term->prompt.content) : 0;
	(term->prompt.location) ? ft_strdel((char **)&term->prompt.location) : 0;
	term->prompt.location = (unsigned char *)getcwd((char *)term->prompt.location, PATH_MAX);
	if ((length = ft_strlens((char *)term->prompt.location)) == 0)
		return ;
	term->prompt.content = (unsigned char *)term_get_folder_name(shell->env, (char *)term->prompt.location, length);
	if ((git = term_get_git_branch(term->prompt.location)))
		term->prompt.content = (unsigned char *)ft_strjoinf((char *)term->prompt.content, git, 3);
	term->prompt.content = (unsigned char *)ft_strjoinf((char *)term->prompt.content, " \e[1;32;40m▸\033[0m ", 1);
	(git)
		? sh_set_prompt_properties(term, 1)
		: sh_set_prompt_properties(term, 0);
}
