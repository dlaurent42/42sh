/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repatriate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:38:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 20:39:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_command_repatriate(t_shell *sh, int i, int len)
{
	while (sh->buffer.parsed[i + len])
	{
		sh->buffer.parsed[i] = sh->buffer.parsed[i + len];
		i++;
	}
	while (sh->buffer.parsed[i])
	{
		sh->buffer.parsed[i] = '\0';
		i++;
	}
}
