/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:57:36 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/10 14:58:01 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		sh_command_test_path(char **arg)
{
	char	*in_pwd;

	if (!arg || !arg[0])
		return (true);
	if ((arg[0][0] == '.' && arg[0][1] == '/') || arg[0][0] == '/')
	{
		if (ft_realpath(&arg[0]) == FALSE)
			return (false);
	}
	else if ((in_pwd = ft_strjoin("./", arg[0])) && access(in_pwd, X_OK) != -1)
	{
		if (ft_realpath(&in_pwd) == FALSE)
		{
			ft_strdel(&in_pwd);
			return (false);
		}
		else
		{
			ft_strdel(&arg[0]);
			arg[0] = in_pwd;
		}
	}
	else
		ft_strdel(&in_pwd);
	return (true);
}
