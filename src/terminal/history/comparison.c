/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 01:38:46 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 01:47:54 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_browse_compare(char *command, char *buffer)
{
	int	i;

	i = 0;
	while (command[i] && buffer[i] && command[i] == buffer[i])
		i++;
	return (buffer[i]);
}
