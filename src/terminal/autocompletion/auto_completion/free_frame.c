/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:44:38 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/18 02:29:43 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				free_frame(t_frame *frame)
{
	free_args(frame, &frame->args);
	free(frame->malloc_failed);
	free(frame->argv);
	free(frame->file_name);
}
