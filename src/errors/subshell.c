/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 19:01:29 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/03 19:01:57 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		error_subshell(void)
{
	ft_putendl_fd("sh: error while executing subshell", 2);
	return (STATUS_ERR);
}
