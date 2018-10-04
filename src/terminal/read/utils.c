/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:08:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 20:28:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_is_select_combination(char *s)
{
	if (s[0] == 11 || s[0] == 22 || s[0] == 24
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x43") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x44") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x46") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x32\x48") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x41") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x42") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x43") == 0
	|| ft_strcmps(s, "\x1b\x5b\x31\x3b\x31\x30\x44") == 0)
		return (TRUE);
	return (FALSE);
}

char	sh_is_arrow_combination(char *s)
{
	if (ft_strcmps(s, "\x1b\x5b\x41") == 0
	|| ft_strcmps(s, "\x1b\x5b\x42") == 0
	|| ft_strcmps(s, "\x1b\x5b\x43") == 0
	|| ft_strcmps(s, "\x1b\x5b\x44") == 0
	|| ft_strcmps(s, "\x1b\x5b\x46") == 0
	|| ft_strcmps(s, "\x1b\x5b\x48") == 0
	|| ft_strcmps(s, "\x1b\x1b\x5b\x41") == 0
	|| ft_strcmps(s, "\x1b\x1b\x5b\x42") == 0
	|| ft_strcmps(s, "\x1b\x1b\x5b\x43") == 0
	|| ft_strcmps(s, "\x1b\x1b\x5b\x44") == 0)
		return (TRUE);
	return (FALSE);
}

char	sh_is_delete_combination(char *s)
{
	unsigned char	c;

	c = (unsigned char)s[0];
	if (c == 1 || c == 2 || c == 5 || c == 6 || c == 8 || c == 127
	|| ft_strcmps(s, "\x1b\x5b\x33\x7e") == 0)
		return (TRUE);
	return (FALSE);
}
