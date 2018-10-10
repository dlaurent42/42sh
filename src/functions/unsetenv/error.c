/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 10:15:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 20:09:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unsetenv_error(char *key, int err_id)
{
	if (err_id == 1)
		ft_putendl_fd("unsetenv: not enough arguments", 2);
	if (err_id == 2)
	{
		ft_putstr_fd("unsetenv: ", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd(" not found", 2);
	}
	if (err_id == 3)
	{
		ft_putstr_fd("unsetenv: cannot unset", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd("", 2);
	}
	ft_strdel(&key);
	return (1);
}
