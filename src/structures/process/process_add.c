/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:26:25 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 14:26:29 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Adds process to end and increses it's id.
*/

void			process_add(t_process **head, t_process *new)
{
	t_process	*cpy;

	cpy = *head;
	if (!(*head))
		*head = new;
	else
	{
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = new;
		new->id = cpy->id + 1;
	}
}
