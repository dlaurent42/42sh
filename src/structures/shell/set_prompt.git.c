/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.git.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:08:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:32:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_get_git_branch_name(t_shell *sh, char *location)
{
	int		fd;
	char	*line;
	char	*position;

	line = NULL;
	if (!(position = ft_strjoins(location, GIT_HEAD)))
		return (NULL);
	if ((fd = open(position, O_RDONLY)) == -1)
	{
		ft_strdel(&position);
		return (NULL);
	}
	if (sh_gnl(sh, fd, &line) == -1)
	{
		ft_strdel(&position);
		return (NULL);
	}
	close(fd);
	ft_strdel(&position);
	return (line);
}

static char	*sh_prompt_get_next_location(char *location)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (location[i])
	{
		if (location[i] == '/')
			j = i;
		i++;
	}
	while (location[j])
	{
		location[j] = '\0';
		j++;
	}
	return (location);
}

static char	*sh_prompt_format_git(char *git)
{
	char	*formatted;

	if (!git)
		return (NULL);
	formatted = (ft_strchrs(git, '/'))
		? ft_strjoins(GIT_NAME_L, git + 16)
		: ft_strjoins(GIT_NAME_L, ft_strleft(git, 7));
	formatted = ft_strjoinf(formatted, GIT_NAME_R, 1);
	ft_strdel(&git);
	return (formatted);
}

char		*sh_get_git_branch(t_shell *sh, char *location)
{
	char			*git;
	DIR				*dir;
	t_dirent		*dirent;

	git = NULL;
	dirent = NULL;
	while (!git)
	{
		if (!(dir = opendir(location)))
			return (NULL);
		while ((dirent = readdir(dir)))
			if (dirent->d_namlen == 4
			&& ft_strcmps(dirent->d_name, GIT_EXT) == 0)
			{
				git = sh_get_git_branch_name(sh, location);
				break ;
			}
		closedir(dir);
		if (!git)
			location = sh_prompt_get_next_location(location);
	}
	return (sh_prompt_format_git(git));
}
