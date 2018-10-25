/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:23:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/25 13:02:45 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		error_pipe(void)
{
	ft_putendl_fd("pipe error", 2);
	return (1);
}

int		error_fork(void)
{
	ft_putendl_fd("fork error", 2);
	return (1);
}

char	error_execution_tree(void)
{
	ft_putendl_fd("error while executing command", 2);
	return (1);
}

char	error_execution_file(char *filename)
{
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
	return (1);
}

char	error_file_permissions(char *filename)
{
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
	return (1);
}
