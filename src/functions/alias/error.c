/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:43:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 16:44:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_alias_error(char *key, char *val, int err_id)
{
	if (err_id == 1)
		ft_putendl_fd("alias: not enough arguments", 2);
	if (err_id == 2)
		ft_putendl_fd("alias: invalid call", 2);
	if (err_id == 3)
	{
		ft_putstr_fd("alias: ", 2);
		ft_putstr_fd(val, 2);
		ft_putendl_fd(" not found", 2);
	}
	if (err_id == 4)
		ft_putendl_fd("alias: environment is full", 2);
	ft_strdel(&key);
	ft_strdel(&val);
	return (1);
}
