/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_not_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:46:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/08 17:06:41 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	sh_is_not_builtin(char *str)
{
	if (ft_strcmps(str, "alias") == 0
	|| ft_strcmps(str, "bg") == 0
	|| ft_strcmps(str, "cd") == 0
	|| ft_strcmps(str, "echo") == 0
	|| ft_strcmps(str, "env") == 0
	|| ft_strcmps(str, "exit") == 0
	|| ft_strcmps(str, "export") == 0
	|| ft_strcmps(str, "fg") == 0
	|| ft_strcmps(str, "help") == 0
	|| ft_strcmps(str, "history") == 0
	|| ft_strcmps(str, "jobs") == 0
	|| ft_strcmps(str, "read") == 0
	|| ft_strcmps(str, "setenv") == 0
	|| ft_strcmps(str, "unalias") == 0
	|| ft_strcmps(str, "unset") == 0
	|| ft_strcmps(str, "unsetenv") == 0)
		return (FALSE);
	return (TRUE);
}
