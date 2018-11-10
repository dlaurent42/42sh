/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:41:05 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 14:02:43 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			redir_add(t_redir **list, t_redir *new)
{
	t_redir		*cpy;

	cpy = *list;
	if (!new || new->front > 10 || new->back > 10)
		return ;
	if (!cpy)
		*list = new;
	else
	{
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = new;
	}
}
