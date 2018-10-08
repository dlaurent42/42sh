/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:16:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 17:40:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_history_usage(void)
{
	ft_putstr_fd("history: usage: history [-c] [-d offset] [n] or", 2);
	ft_putendl_fd(" history -awrn [filename] or history -ps arg [arg...]", 2);
}

char		sh_history_error(int err_id)
{
	if (err_id == 1)
		ft_putendl_fd("history: numeric argument (int) required", 2);
	if (err_id == 2)
		ft_putendl_fd("history: too many arguments", 2);
	if (err_id == 3)
		ft_putendl_fd("history: invalid option", 2);
	if (err_id == 4)
		ft_putendl_fd("history: -d: option requires an argument", 2);
	if (err_id == 5)
		ft_putendl_fd("history: history position out of range", 2);
	sh_history_usage();
	return (1);
}
