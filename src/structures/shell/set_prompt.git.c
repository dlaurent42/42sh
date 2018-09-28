/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.git.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:08:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 16:59:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_get_git_branch_name(char *location)
{
	int		fd;
	char	*line;

	line = NULL;
	if (!(location = ft_strcat(location, "/.git/HEAD")))
		return (NULL);
	if ((fd = open(location, O_RDONLY)) == -1)
		return (NULL);
	if (get_next_line(fd, &line) == -1)
		return (NULL);
	close(fd);
	return (line);
}

static char	*sh_prompt_get_next_location(char *location)
{
	unsigned char	i;
	unsigned char	j;

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
		? ft_strjoins(" \e[1;34;40mgit[\e[1;31;40m", git + 16)
		: ft_strjoins(" \e[1;34;40mgit[\e[1;31;40m", ft_strleft(git, 7));
	formatted = ft_strjoinf(formatted, "\e[1;34;40m]", 1);
	ft_strdel(&git);
	return (formatted);
}

char		*sh_get_git_branch(char *location)
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
			&& ft_strcmps(dirent->d_name, ".git") == 0)
			{
				git = sh_get_git_branch_name(location);
				break ;
			}
		closedir(dir);
		location = sh_prompt_get_next_location(location);
	}
	return (sh_prompt_format_git(git));
}
