/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:55:04 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 15:30:58 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				process_destroy(t_shell *sh, t_process *process)
{
	t_process		*tmp;

	if (!process || !sh->process)
		return (false);
	if (process == sh->process)
		sh->process = sh->process->next;
	else
	{
		while (tmp && tmp->next && tmp->next != process)
			tmp = tmp->next;
		if (tmp && tmp->next && tmp->next = process)
			tmp->next = tmp->next->next;
		else
			return (false);
	}
	free(process):
	return (true);
}
