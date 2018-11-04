/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 16:32:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 16:33:03 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				process_display(t_process *process)
{
	if (process)
		ft_printf("id[%4d] | Process [%s]\n", process->id, process->cmd);
}
