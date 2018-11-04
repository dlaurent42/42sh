/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 13:24:37 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/04 13:29:44 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process			*process_new(void)
{
	t_process		*ret;

	if (!(ret = (t_process *)ft_memalloc(sizeof(t_process))))
		return (NULL);
	ret->id = 0;
	ft_bzero((int)fd, sizeof(int) * 10);
	ret->status = 0;
	ret->pid = -1;
	ret->cmd = NULL;
	ret->next = NULL;
	ret->head = NULL;
	return (ret)
}
