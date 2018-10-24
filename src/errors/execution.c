/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:23:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 16:29:30 by azaliaus         ###   ########.fr       */
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
