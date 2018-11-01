/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ac.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:44:38 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 18:37:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_free_ac(t_shell *sh)
{
	(sh->ac->obj) ? auto_free_obj(&sh->ac->obj) : 0;
	(sh->ac->bin) ? auto_free_obj(&sh->ac->bin) : 0;
	(sh->ac->env) ? auto_free_obj(&sh->ac->env) : 0;
	(sh->ac->file_name) ? free(sh->ac->file_name) : 0;
	(sh->ac) ? free(sh->ac) : 0;
	sh->ac = NULL;
}
