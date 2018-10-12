/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:04:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:04:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*move_past_leading_spaces(char *content)
{
	while (content && *content == ' ')
		content++;
	return (content);
}

bool			contains_printable_characters(char *str)
{
	while (str && *str)
	{
		if (ft_isprint(*str))
			return (true);
		str++;
	}
	return (false);
}
