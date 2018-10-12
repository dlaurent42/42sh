/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ac.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:44:38 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:19:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
