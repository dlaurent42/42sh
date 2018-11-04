/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 13:24:37 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/04 14:24:11 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process			*process_new(void)
{
	t_process		*new_process;

	if (!(new_process = (t_process *)ft_memalloc(sizeof(t_process))))
		return (NULL);
	new_process->pid = -1;
	return (new_process)
}
