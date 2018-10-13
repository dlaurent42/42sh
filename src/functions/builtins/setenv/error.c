/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:01:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 18:54:07 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_setenv_error(char *key, char *val, int err_id)
{
	if (err_id == 1)
		ft_putendl_fd("setenv: not enough arguments", 2);
	if (err_id == 2)
		ft_putendl_fd("setenv: invalid call", 2);
	if (err_id == 3)
	{
		ft_putstr_fd("setenv: ", 2);
		ft_putstr_fd(val, 2);
		ft_putendl_fd(" is protected", 2);
	}
	if (err_id == 4)
	{
		ft_putstr_fd("setenv: ", 2);
		ft_putstr_fd(val, 2);
		ft_putendl_fd(" not found", 2);
	}
	if (err_id == 5)
		ft_putendl_fd("setenv: environment is full", 2);
	ft_strdel(&key);
	ft_strdel(&val);
	return (1);
}
