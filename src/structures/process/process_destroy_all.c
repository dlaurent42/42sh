/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_destroy_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:11:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 18:15:11 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				process_destroy_all(t_shell *sh)
{
	if (!sh->process)
		return (false);
	while (sh->process)
		process_destroy(sh, sh->process);
	return (true);
}
