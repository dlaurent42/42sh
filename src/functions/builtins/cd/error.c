/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:06:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 20:30:54 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_cd_error(char *value, char *path, int err_id)
{
	if (err_id == 1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	if (err_id == 2)
		ft_putstr_fd("cd: too many levels of symbolic links: ", 2);
	if (err_id == 3)
		ft_putstr_fd("cd: permission denied: ", 2);
	if (err_id == 4)
		ft_putendl_fd("cd: too many arguments", 2);
	if (err_id == 5)
		ft_putendl_fd("cd: HOME not set", 2);
	if (err_id == 6)
		ft_putendl_fd("cd: OLDPWD not set", 2);
	if (err_id == 7)
		ft_putstr_fd("cd: File name too long: ", 2);
	if (err_id != 4)
		ft_putendl_fd(value, 2);
	ft_strdel(&path);
	return (1);
}
