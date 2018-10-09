/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ac.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:44:38 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 19:22:08 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

void				auto_free_ac(t_shell *sh)
{
	auto_free_obj(&sh->ac->obj);
	auto_free_obj(&sh->ac->bin);
	auto_free_obj(&sh->ac->env);
	free(sh->ac->argv);
	free(sh->ac->file_name);
	free(sh->ac->pre_file_name);
	free(sh->ac);
	sh->ac = NULL;
}
