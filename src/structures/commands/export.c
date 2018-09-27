/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 18:57:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 20:20:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	command_export_error(int fd, char *path)
{
	(path) ? remove(path) : 0;
	(path) ? ft_strdel(&path) : 0;
	(fd != -1) ? close(fd) : 0;
}

void		command_export_all(t_shell *sh)
{
	int		fd;
	char	*id;
	char	*path;
	t_cmd	*cmd;

	if (!sh->cmd
	|| !(path = env_search(sh->env, "HOME"))
	|| !(path = ft_strjoins(path, "/.cmd_history")))
		return ;
	remove(path);
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE)) == -1)
		return (command_export_error(fd, path));
	cmd = sh->cmd->last;
	ft_putendl_fd(VERIF_KEY, fd);
	while (cmd)
	{
		id = ft_itoa(cmd->id);
		ft_putstr_fd(id, fd);
		ft_putchar_fd(':', fd);
		ft_putendl_fd(cmd->cmd, fd);
		ft_strdel(&id);
		cmd = cmd->prev;
	}
	ft_strdel(&path);
}
