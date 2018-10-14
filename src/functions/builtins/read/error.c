/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:45:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/14 18:11:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_read_usage(void)
{
	ft_putstr_fd("read: usage: read [-ers] [-u fd] [-t timeout] [-p pro", 2);
	ft_putendl_fd("mpt] [-a array] [-n nchars] [-d delim] [name ...]", 2);
}

static char	sh_read_error_next(char c, char err_id)
{
	(void)c;
	if (err_id == 4)
		ft_putendl_fd("unknown error", 2);
	if (err_id == 3)
		ft_putendl_fd("invalid number", 2);
	if (err_id == 5)
		ft_putendl_fd("invalid timeout specification", 2);
	if (err_id == 6)
		ft_putendl_fd("invalid file descriptor specification", 2);
	if (err_id == 7)
		ft_putendl_fd("invalid file descriptor: Bad file descriptor", 2);
	sh_read_usage();
	return (1);
}

char		sh_read_error(char c, char err_id)
{
	ft_putstr_fd("read: ", 2);
	if (err_id >= 3)
		return (sh_read_error_next(c, err_id));
	if (err_id == 1)
	{
		ft_putchar_fd('-', 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd(": invalid option", 2);
	}
	if (err_id == 2)
	{
		ft_putstr_fd("argument expected: -", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
	}
	sh_read_usage();
	return (1);
}

char		sh_read_error_msg(char *s, char err_id)
{
	if (err_id == 1)
	{
		ft_putstr_fd("read: `", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		sh_read_usage();
	}
	else if (err_id == 2)
		ft_putendl_fd(s, 2);
	return (1);
}
