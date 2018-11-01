/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:35:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 20:45:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_glob	*sh_glob_init(t_glob *glob, char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!(glob = (t_glob *)ft_memalloc(sizeof(t_glob))))
		return (NULL);
	glob->starts_by_path = (str[0] == '/') ? TRUE : FALSE;
	glob->ends_by_path = (str[ft_strlens(str) - 1] == '/') ? TRUE : FALSE;
	glob->strsplit = pattern_strsplit(str, '/');
	while (glob->strsplit[count])
		count++;
	if (count == 0 && glob->starts_by_path)
		count = 1;
	if (!(glob->fs = (t_filesystem **)ft_memalloc(
			sizeof(t_filesystem *) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		glob->fs[i] = (t_filesystem *)ft_memalloc(sizeof(t_filesystem));
		i++;
	}
	sh_glob_add_initial_path(glob);
	return (glob);
}

static void		sh_glob_delete_filesystem(t_filesystem *fs)
{
	int		i;
	t_path	*path;

	i = 0;
	while (fs->lst[i])
	{
		ft_strdel(&fs->lst[i]);
		i++;
	}
	while (fs->paths)
	{
		path = fs->paths->next;
		ft_strdel(&fs->paths->path);
		free(fs->paths);
		fs->paths = path;
	}
	free(fs);
}

static char		*sh_glob_pattern_final(t_glob *glob)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = -1;
	result = (glob->result) ? ft_strdups(glob->result) : NULL;
	while (glob->fs[++i])
		sh_glob_delete_filesystem(glob->fs[i]);
	while (glob->strsplit[++j])
		ft_strdel(&glob->strsplit[j]);
	ft_strdel(&glob->result);
	free(glob->strsplit);
	free(glob->fs);
	free(glob);
	return (result);
}

char			*sh_glob_pattern(char *str)
{
	int			i;
	t_glob		*glob;

	i = 0;
	if (!str)
		return (NULL);
	glob = sh_glob_init(NULL, str);
	while (glob && glob->strsplit[i])
	{
		glob->strsplit[i] = glob_remove_wildcars(glob->strsplit[i]);
		glob->strsplit[i] = sh_glob_expand_ranges(
			glob->fs[i], glob->strsplit[i]);
		if (ft_strcmps(glob->strsplit[i], "**") == 0)
			sh_glob_check_all_paths(glob, glob->fs[i], glob->fs[i + 1]);
		else if (glob->fs[i + 1])
			sh_glob_check_paths(
				glob, glob->fs[i], glob->strsplit[i], glob->fs[i + 1]);
		else
			sh_glob_check_final_paths(glob, glob->fs[i], glob->strsplit[i]);
		i++;
	}
	return (sh_glob_pattern_final(glob));
}
