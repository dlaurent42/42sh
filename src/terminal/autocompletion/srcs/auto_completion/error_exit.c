/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:57:51 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/14 23:53:34 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void				error_exit(t_frame *frame, char *error_str)
{
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	free_frame(frame);
	exit(1);
}