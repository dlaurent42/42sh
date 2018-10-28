/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:23:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 00:10:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** if ((env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size))
**		env_insert_protected(sh, sh->env, "?", "1");
*/

int		error_pipe(void)
{
	ft_putendl_fd("pipe error", 2);
	return (STATUS_ERR);
}

int		error_fork(void)
{
	ft_putendl_fd("fork error", 2);
	return (STATUS_ERR);
}

char	error_execution_tree(void)
{
	ft_putendl_fd("error while executing command", 2);
	return (STATUS_ERR);
}

char	error_execution_file(t_shell *sh, char *filename)
{
	if (access(filename, F_OK) != -1 && access(filename, R_OK) == -1)
		return (error_file_permissions(sh, filename));
	if ((env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size))
		env_insert_protected(sh, sh->env, "?", "127");
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
	return (STATUS_NOT_FOUND);
}

char	error_file_permissions(t_shell *sh, char *filename)
{
	if ((env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size))
		env_insert_protected(sh, sh->env, "?", "126");
	ft_putstr_fd("permission denied: ", 2);
	ft_putendl_fd(filename, 2);
	return (STATUS_PERMISSION_DENIED);
}
