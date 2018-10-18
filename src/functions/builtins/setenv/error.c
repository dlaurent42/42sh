/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:01:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 14:02:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_setenv_error(char *key, char *val, int err_id, char *msg)
{
	(err_id == 1 && msg) ? ft_putstr_fd("setenv: -", 2) : 0;
	(err_id == 1 && !msg) ? ft_putstr_fd("setenv", 2) : 0;
	(err_id == 1 && msg) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 1) ? ft_putendl_fd(": unknown option", 2) : 0;
	(err_id == 1) ? ft_putendl_fd("Usage: setenv [-p] [name[=value]...]", 2)
		: 0;
	(err_id == 2) ? ft_putendl_fd("setenv: invalid format", 2) : 0;
	(err_id == 3) ? ft_putstr_fd("setenv: ", 2) : 0;
	(err_id == 3) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 3) ? ft_putendl_fd(" not found", 2) : 0;
	(err_id == 4) ? ft_putendl_fd("setenv: environment is full", 2) : 0;
	(err_id == 5 && msg) ? ft_putstr_fd("setenv: ", 2) : 0;
	(err_id == 5 && msg) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 5 && msg) ? ft_putendl_fd(" is already public", 2) : 0;
	(err_id == 6 && msg) ? ft_putstr_fd("setenv: ", 2) : 0;
	(err_id == 6 && msg) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 6 && msg) ? ft_putendl_fd(" is protected keyword", 2) : 0;
	(err_id == 7) ? ft_putstr_fd("setenv: ", 2) : 0;
	(err_id == 7) ? ft_putstr_fd(key, 2) : 0;
	(err_id == 7) ? ft_putendl_fd(" is protected keyword", 2) : 0;
	ft_strdel(&key);
	ft_strdel(&val);
	return (1);
}
