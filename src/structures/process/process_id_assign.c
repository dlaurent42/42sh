/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_id_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:25:12 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 18:29:23 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				process_id_assign(t_shell *sh)
{
	int				id;
	t_process		*process;

	id = 0;
	process = sh->process;
	while (process)
	{
		id++;
		process = process->next;
	}
	process = sh->process;
	while (process)
	{
		process->id = id--;
		process = process->next;
	}
}
