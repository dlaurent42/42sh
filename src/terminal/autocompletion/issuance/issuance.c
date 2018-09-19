/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/17 08:43:47 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				issuance(t_frame *frame)
{
	frame->current_args = frame->args;
	get_attributes(frame);
	sort(frame);
	frame->args = frame->current_args;
	loop_dirs(frame);
}
