/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 20:21:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:33:31 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_set_prompt_properties(t_shell *sh, unsigned char has_git)
{
	unsigned char	i;

	i = 0;
	sh->prompt.len = 0;
	while (sh->prompt.content[i])
	{
		if ((unsigned char)sh->prompt.content[i] >= 0b11000000
		|| (unsigned char)sh->prompt.content[i] < 0b10000000)
			sh->prompt.len++;
		i++;
	}
	sh->prompt.len -= (has_git) ? 54 : 24;
	sh->prompt.len_mod = sh->prompt.len % sh->window.width;
	sh->prompt.rows = sh->prompt.len / sh->window.width + 1;
}

static void	sh_set_prompt_location(t_shell *sh)
{
	size_t		len;
	char		*curr_location;

	curr_location = NULL;
	if (sh->env && env_search(sh->env, "PWD"))
	{
		if (sh->prompt.location
		&& ft_strcmps(env_search(sh->env, "PWD"), sh->prompt.location) == 0)
			return ;
		ft_strdel(&sh->prompt.location);
		sh->prompt.location = ft_strdups(env_search(sh->env, "PWD"));
	}
	else if ((curr_location = getcwd(curr_location, PATH_MAX)))
	{
		ft_strdel(&sh->prompt.location);
		sh->prompt.location = curr_location;
	}
	len = ft_strlens(sh->prompt.location);
	while (--len && sh->prompt.location[len] == '/')
		sh->prompt.location[len] = '\0';
}

void		sh_set_prompt(t_shell *sh)
{
	char	*git;
	size_t	len;

	git = NULL;
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	sh_set_prompt_location(sh);
	if ((len = ft_strlens(sh->prompt.location)) == 0)
		return ;
	sh->prompt.content = sh_get_folder_name(sh->env, sh->prompt.location, len);
	sh_set_prompt_location(sh);
	if ((git = sh_get_git_branch(sh, sh->prompt.location)))
		sh->prompt.content = ft_strjoinf(sh->prompt.content, git, 3);
	sh->prompt.content = (ft_atoi(env_search(sh->env, "?")) == 0)
		? ft_strjoinf(sh->prompt.content, VALID_PROMPT, 1)
		: ft_strjoinf(sh->prompt.content, ERR_PROMPT, 1);
	(git)
		? sh_set_prompt_properties(sh, 1)
		: sh_set_prompt_properties(sh, 0);
	sh_set_prompt_location(sh);
}
