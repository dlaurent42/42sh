/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:43:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 13:16:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_alias_error(char *key, char *val, int err_id, char *msg)
{
	if (err_id == 1)
	{
		(msg) ? ft_putstr_fd("alias: -", 2) : ft_putstr_fd("alias", 2);
		(msg) ? ft_putstr_fd(msg, 2) : 0;
		ft_putendl_fd(": unknown option", 2);
		ft_putendl_fd("Usage: alias [-p] [name[=value]...]", 2);
	}
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
