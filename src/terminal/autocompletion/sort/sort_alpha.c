/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 11:59:00 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 00:22:31 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_sort_alpha(t_shell *shell)
{
	if (ft_strcmp(shell->ac->track->data.str, shell->ac->track->next->data.str) > 0)
		return (true);
	return (false);
}
