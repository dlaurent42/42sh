/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:35:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 14:48:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//
//	Initial string		:	***[a-fG-K]?*b[abcd]/***[a-fG-K]?*b[!abcd]oklm/**/*.[ch]
//	Parsed string (1)	:	*[a-fG-K]?*b[abcd]/*[a-fG-K]?*b[!abcd]oklm/**/*.[ch]
//	Parsed string (2)	:	*[abcdefGHIJK]?*b[abcd]/*[abcdefGHIJK]?*b[!abcd]oklm/**/*.[ch]
//	Parsed string (3)	:	Replace '?' by [all printable possibilities except '/']
//	Parsed string (4)	:	Replace [!...] by the contrary of what is inside brackets
//	SplitA string		:	*[abcdefGHIJK][a...9]*b[abcd]
//							*[abcdefGHIJK][a...9]*b[e...z0...9A...Z]oklm
//							**
//							*.[ch]
//	SplitB each splitA:
//		*
//		[abcdefGHIJK]
//		[a...9]
//		*
//		b
//		[abcd]
//	add '/' if not last element of splitA
//
/*
	while (splitA[i])
	{
		while (splitB[j])
		
	}
*/

/*
	STRUCTURE NEEDED

	|>	strsplit A
	|>	FILESYSTEM
	|----> 	possible paths as linked list
	|---->	strsplit B
	|---->	nb_list of type [sad]
	|---->  array of indexes for lists
*/

static void	sh_glob_fs_init(t_glob *glob)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (glob->strsplit[count])
		count++;
	if (!(glob->fs = (t_filesystem **)ft_memalloc(sizeof(t_filesystem *) * (count + 1))))
		return ;
	ft_printf(". sh_glob_fs_init: count is %d\n", count);
	while (i < count)
	{
		glob->fs[i] = (t_filesystem *)ft_memalloc(sizeof(t_filesystem));
		i++;
	}
	sh_glob_add_initial_path(glob);
}

static void	sh_glob_delete_filesystem(t_filesystem *fs)
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

static char	*sh_glob_pattern_final(t_glob *glob)
{
	int		i;
	char	*result;

	i = 0;
	result = (glob->result) ? ft_strdups(glob->result) : NULL;
	while (glob->strsplit[i])
	{
		ft_strdel(&glob->strsplit[i]);
		sh_glob_delete_filesystem(glob->fs[i]);
		i++;
	}
	ft_strdel(&glob->result);
	free(glob->strsplit);
	free(glob->fs);
	free(glob);
	return (result);
}

char		*sh_glob_pattern(char *str)
{
	int			i;
	t_glob		*glob;

	i = 0;
	if (!str)
		return (NULL);
	if (!(glob = (t_glob *)ft_memalloc(sizeof(t_glob))))
		return (NULL);
	ft_printf("sh_glob_pattern received: [%s]\n", str);
	glob->starts_by_path = (str[0] == '/') ? TRUE : FALSE;
	glob->ends_by_path = (str[ft_strlens(str) - 1] == '/') ? TRUE : FALSE;
	glob->strsplit = pattern_strsplit(str, '/');
	sh_glob_fs_init(glob);	
	while (glob->strsplit[i])
	{
		ft_printf("... sh_glob_pattern starts with: [%s] [%d]\n", glob->strsplit[i], i);
		glob->strsplit[i] = glob_remove_wildcars(glob->strsplit[i]);
		glob->strsplit[i] = sh_glob_expand_ranges(glob->fs[i], glob->strsplit[i]);
		ft_printf("... sh_glob_pattern parsed [%s]\n", glob->strsplit[i]);
		if (ft_strcmps(glob->strsplit[i], "**") == 0)
			sh_glob_check_all_paths(glob, glob->fs[i], glob->fs[i + 1]);
		else if (glob->fs[i + 1])
			sh_glob_check_paths(glob, glob->fs[i], glob->strsplit[i], glob->fs[i + 1]);
		else
			sh_glob_check_final_paths(glob, glob->fs[i], glob->strsplit[i]);
		i++;
	}
	return (sh_glob_pattern_final(glob));
}
