/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:38:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:19:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_merge_objs(t_shell *sh, t_obj *head)
{
	t_obj			*obj;

	obj = head;
	if (sh->ac->auto_mode == AUTO_BIN)
	{
		while (obj && obj->next)
			obj = obj->next;
		obj->next = sh->ac->bin;
		sh->ac->bin = NULL;
	}
	if (sh->ac->auto_mode == AUTO_BIN || sh->ac->auto_mode == AUTO_ENV)
	{
		while (obj && obj->next)
			obj = obj->next;
		obj->next = sh->ac->env;
		sh->ac->env = NULL;
	}
}
