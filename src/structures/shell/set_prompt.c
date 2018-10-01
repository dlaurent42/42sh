/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 20:21:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 20:08:02 by dlaurent         ###   ########.fr       */
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

static void	sh_set_prompt_location(t_shell *sh, char flag)
{
	(sh->prompt.location) ? ft_strdel(&sh->prompt.location) : 0;
	if (flag == 1)
		if (!(sh->prompt.location = ft_strdup(env_search(sh->env, "PWD"))))
			sh->prompt.location = getcwd(sh->prompt.location, PATH_MAX);
	if (flag == 0)
		sh->prompt.location = getcwd(sh->prompt.location, PATH_MAX);
}

void		sh_set_prompt(t_shell *sh)
{
	char	*git;
	size_t	len;

	git = NULL;
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	sh_set_prompt_location(sh, 1);
	if ((len = ft_strlens(sh->prompt.location)) == 0)
		return ;
	sh->prompt.content = sh_get_folder_name(sh->env, sh->prompt.location, len);
	sh_set_prompt_location(sh, 0);
	if ((git = sh_get_git_branch(sh->prompt.location)))
		sh->prompt.content = ft_strjoinf(sh->prompt.content, git, 3);
	sh->prompt.content = (sh->prompt.last_exec_succeed == 0)
		? ft_strjoinf(sh->prompt.content, " \e[1;32;40m▸\033[0m ", 1)
		: ft_strjoinf(sh->prompt.content, " \e[1;31;40m▸\033[0m ", 1);
	(git)
		? sh_set_prompt_properties(sh, 1)
		: sh_set_prompt_properties(sh, 0);
	sh_set_prompt_location(sh, 1);
}
