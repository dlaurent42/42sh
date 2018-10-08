/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_special_modes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:59:47 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 00:26:00 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static void			filter_cd(t_shell *sh, t_obj *obj)
{
	(void)sh;
	while (obj)
	{
		if (!obj->data.dir)
			obj->data.no_file = 1;
		obj = obj->next;
	}
}

void				auto_do_special_modes(t_shell *sh, t_obj *obj)
{
	char			*space;

	if (!(space = ft_strchr(sh->buffer.content, ' ')))
		return ;
	if (!ft_strncmp(sh->buffer.content, "cd", space - sh->buffer.content))
		filter_cd(sh, obj);
}
