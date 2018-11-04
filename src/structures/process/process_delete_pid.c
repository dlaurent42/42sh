/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_delete_pid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:44:42 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 15:45:09 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				process_delete_pid(t_shell *sh, pid_t pid)
{
	return (process_destroy(sh, process_get_pid(sh, pid));
}
