/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:44:12 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 13:52:36 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			redir_destroy(t_redir **list)
{
	t_redir		*cpy;
	t_redir		*tmp;

	cpy = *list;
	if (!cpy)
		return ;
	while (cpy)
	{
		tmp = cpy;
		cpy = cpy->next;
		free(tmp);
	}
	*list = NULL;
}
