/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:08:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 17:31:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_is_select_combination(char *s)
{
	if (s[0] == 11 || s[0] == 16 || s[0] == 24
	|| ft_strcmps(s, K_S_RIGHT) == 0
	|| ft_strcmps(s, K_S_LEFT) == 0
	|| ft_strcmps(s, K_S_END) == 0
	|| ft_strcmps(s, K_S_HOME) == 0
	|| ft_strcmps(s, K_S_O_UP) == 0
	|| ft_strcmps(s, K_S_O_DOWN) == 0
	|| ft_strcmps(s, K_S_O_RIGHT) == 0
	|| ft_strcmps(s, K_S_O_LEFT) == 0)
		return (TRUE);
	return (FALSE);
}

char	sh_is_arrow_combination(char *s)
{
	if (ft_strcmps(s, K_UP) == 0
	|| ft_strcmps(s, K_DOWN) == 0
	|| ft_strcmps(s, K_RIGHT) == 0
	|| ft_strcmps(s, K_LEFT) == 0
	|| ft_strcmps(s, K_END) == 0
	|| ft_strcmps(s, K_HOME) == 0
	|| ft_strcmps(s, K_O_UP) == 0
	|| ft_strcmps(s, K_O_DOWN) == 0
	|| ft_strcmps(s, K_O_RIGHT) == 0
	|| ft_strcmps(s, K_O_LEFT) == 0)
		return (TRUE);
	return (FALSE);
}

char	sh_is_delete_combination(char *s)
{
	unsigned char	c;

	c = (unsigned char)s[0];
	if (c == 1 || c == 2 || c == 5 || c == 6 || c == 8 || c == 127
	|| ft_strcmps(s, K_F_DEL) == 0)
		return (TRUE);
	return (FALSE);
}
