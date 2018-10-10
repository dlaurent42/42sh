/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:38:30 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/11 00:19:10 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

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
