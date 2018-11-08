/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:55:04 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/08 22:19:42 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				process_destroy(t_shell *sh, t_process *process)
{
	t_process		*tmp;

	tmp = sh->process;
	if (!process || !sh->process)
		return (false);
	if (process == sh->process)
		sh->process = sh->process->next;
	else
	{
		while (tmp && tmp->next && tmp->next != process)
			tmp = tmp->next;
		if (tmp && tmp->next && tmp->next == process)
			tmp->next = tmp->next->next;
		else
			return (false);
	}
	free(process);
	return (true);
}
