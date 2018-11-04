/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_delete_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:42:47 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 15:44:02 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				process_delete_id(t_shell *sh, int id)
{
	return (process_destroy(sh, process_get_id(sh, id));
}
