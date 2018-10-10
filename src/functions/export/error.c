/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:10:00 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:19:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_export_error(char *key, char *val, int err_id, char *msg)
{
	if (err_id == 1)
	{
		(msg) ? ft_putstr_fd("export: -", 2) : ft_putstr_fd("export", 2);
		(msg) ? ft_putstr_fd(msg, 2) : 0;
		ft_putendl_fd(": unknown option", 2);
		ft_putendl_fd("Usage: export [-p] [name[=value]...]", 2);
	}
	if (err_id == 2)
		ft_putendl_fd("export: invalid call", 2);
	if (err_id == 3)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(val, 2);
		ft_putendl_fd(" not found", 2);
	}
	if (err_id == 4)
		ft_putendl_fd("export: environment is full", 2);
	ft_strdel(&key);
	ft_strdel(&val);
	return (1);
}
