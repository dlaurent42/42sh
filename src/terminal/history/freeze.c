/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:46:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 14:49:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_browse_freeze(t_shell *sh)
{
	sh->buffer.cmd = NULL;
	ft_bzero(sh->buffer.stored, ARG_MAX + 1);
	sh->modes.browse = FALSE;
}
