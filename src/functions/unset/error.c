/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:35:36 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:44:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unset_error(char *key, int err_id)
{
	if (err_id == 1)
		ft_putendl_fd("unset: not enough arguments", 2);
	if (err_id == 2)
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd(" not found locally", 2);
	}
	if (err_id == 3)
	{
		ft_putstr_fd("unset: cannot unset", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd("", 2);
	}
	ft_strdel(&key);
	return (1);
}
