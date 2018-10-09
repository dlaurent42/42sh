/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 18:57:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 15:15:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	command_export_error(int fd, char *path)
{
	(path) ? remove(path) : 0;
	(path) ? ft_strdel(&path) : 0;
	(fd != -1) ? close(fd) : 0;
}

void		command_export_to(t_shell *sh, char *path)
{
	int		fd;
	char	*id;
	t_cmd	*cmd;

	if (!path && !(path = env_search(sh->local_env, "HISTFILE")))
		return (0);
	remove(path);
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE)) == -1)
		return (command_export_error(fd, path));
	ft_putendl_fd(VERIF_KEY, fd);
	if (!sh->cmd)
		return ((void)close(fd));
	cmd = sh->cmd->last;
	while (cmd)
	{
		id = ft_itoa(cmd->id);
		ft_putstr_fd(id, fd);
		ft_putchar_fd(':', fd);
		ft_putendl_fd(cmd->content, fd);
		ft_strdel(&id);
		cmd = cmd->prev;
	}
	close(fd);
}

void		command_export_all(t_shell *sh)
{
	int		fd;
	char	*id;
	char	*path;
	t_cmd	*cmd;

	if (!sh->cmd
	|| !(path = env_search(sh->local_env, "HISTFILE")))
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
		ft_putendl_fd(cmd->content, fd);
		ft_strdel(&id);
		cmd = cmd->prev;
	}
	close(fd);
}
