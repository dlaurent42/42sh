/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:57:51 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/20 00:47:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				error_exit(t_frame *frame, char *error_str)
{
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	free_frame(frame);
	exit(1);
}
