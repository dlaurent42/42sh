/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:32:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:58:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_glob_add_initial_path(t_glob *glob)
{
	t_path	*new;

	if (!(new = (void *)ft_memalloc(sizeof(t_path))))
		return ;
	new->path = (glob->starts_by_path)
		? ft_strdups("/")
		: ft_strjoinf(getcwd(new->path, PATH_MAX), "/", 1);
	glob->fs[0]->paths = new;
}

void		sh_glob_add_path(t_filesystem *fs, char *path, char *name)
{
	t_path	*new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
		return ;
	new->path = (path && path[ft_strlen(path) - 1] != '/')
		? ft_strjoins(path, "/")
		: ft_strdups(path);
	new->path = ft_strjoinf(new->path, name, 1);
	new->next = (fs && fs->paths) ? fs->paths : NULL;
	fs->paths = new;
}

static char	*sh_glob_check_result(char *str)
{
	int		i;
	char	*new;
	char	*left;
	char	*right;

	i = 0;
	left = NULL;
	right = NULL;
	new = ft_strdupf(str);
	while (new[i])
	{
		if (lexer_need_esc(new[i]) && !lexer_is_esc(new, i))
		{
			left = ft_strsub(new, 0, i);
			right = ft_strdups(new + i);
			ft_strdel(&new);
			new = ft_strjoinf(left, "\\", 1);
			new = ft_strjoinf(new, right, 3);
			i++;
		}
		if (new[i])
			i++;
	}
	return (new);
}

static char	*sh_glob_remove_dbl_slash(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] == '/')
			lexer_repatriate(str, i, 1);
		i++;
	}
	return (str);
}

void		sh_glob_add_result(t_glob *glob, char *path, char *name)
{
	char	*result;
	char	*curr_path;

	curr_path = NULL;
	result = ft_strjoins(path, "/");
	result = ft_strjoinf(result, name, 1);
	result = sh_glob_remove_dbl_slash(result);
	if (glob->ends_by_path)
		result = ft_strjoinf(result, "/", 1);
	(glob->result) ? glob->result = ft_strjoinf(glob->result, " ", 1) : 0;
	if (!glob->starts_by_path)
	{
		curr_path = getcwd(curr_path, PATH_MAX);
		glob->result = ft_strjoinf(
			glob->result,
			sh_glob_check_result(
				ft_strdups(result + ft_strlens(curr_path) + 1)), 3);
		ft_strdel(&curr_path);
		ft_strdel(&result);
	}
	else
		glob->result = ft_strjoinf(glob->result,
		sh_glob_check_result(result), 3);
}
