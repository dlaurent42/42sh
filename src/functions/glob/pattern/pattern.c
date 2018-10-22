/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:35:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/21 20:20:23 by dlaurent         ###   ########.fr       */
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

// STARTS BY A SLASH ?
// ENDS BY A SLASH ?


char	*sh_glob_pattern(char *str)
{
	t_glob		*glob;

	if (!(glob = (t_glob *)ft_memalloc(sizeof(t_glob))))
		return (NULL);
	ft_printf("sh_glob_patten received: [%s]\n", str);
	glob->initial_str = ft_strdups(str);
	glob->parsed_str = ft_strdups(str);
	glob->last_is_path = (str[ft_strlens(str) - 1] == '/') ? TRUE : FALSE;
	glob->strsplit = pattern_strsplit(str, '/');
	glob->parsed_str = glob_remove_wildcars(glob->parsed_str);
	glob->parsed_str = sh_glob_expand_ranges(glob->parsed_str);
	ft_printf("sh_glob_pattern returned: [%s]\n", glob->parsed_str);
	return (glob->parsed_str);
}
