/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repatriate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:38:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:55:47 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_repatriate(char *str, int i, int len)
{
	while (str[i + len])
	{
		str[i] = str[i + len];
		i++;
	}
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}
