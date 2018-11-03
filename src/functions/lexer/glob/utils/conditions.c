/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:55:45 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/03 13:55:51 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool			glob_conditions(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && !lexer_is_esc(str, i))
			return (FALSE);
		if ((str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == '{')
		&& !lexer_is_esc(str, i))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
