/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 22:27:36 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

void				auto_issuance(t_shell *sh)
{
	sh->ac->current_obj = sh->ac->obj;
	if (!auto_get_attributes(sh))
		return ;
	sh->ac->obj = sh->ac->current_obj;
	if (sh->ac->obj->data.dir && !sh->ac->obj->data.no_file)
		auto_do_ls(sh, sh->ac->obj);
}
