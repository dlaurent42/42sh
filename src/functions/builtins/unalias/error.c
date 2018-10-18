/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:35:36 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 14:04:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unalias_error(char *key, int err_id)
{
	if (err_id == 1)
		ft_putendl_fd("unalias: not enough arguments", 2);
	if (err_id == 2)
	{
		ft_putstr_fd("unalias: ", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd(" not found", 2);
	}
	if (err_id == 3)
	{
		ft_putstr_fd("unalias: cannot unalias", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd("", 2);
	}
	ft_strdel(&key);
	return (1);
}
