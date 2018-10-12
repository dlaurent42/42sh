/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:19:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_issuance(t_shell *sh)
{
	sh->ac->current_obj = sh->ac->obj;
	if (!auto_get_attributes(sh))
		return ;
	sh->ac->obj = sh->ac->current_obj;
	if (sh->ac->obj->data.dir && !sh->ac->obj->data.no_file)
		auto_do_ls(sh, sh->ac->obj);
}
