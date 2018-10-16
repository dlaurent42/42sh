/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 18:57:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 19:49:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		command_export_all(t_shell *sh)
{
	int		fd;
	char	*path;
	t_cmd	*cmd;

	if (!sh->cmd
	|| !(path = env_search(sh->env, "HISTFILE")))
		return ;
	remove(path);
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE)) == -1)
		return (error_import_export(fd, path));
	cmd = sh->cmd->last;
	ft_putendl_fd(VERIF_KEY, fd);
	while (cmd)
	{
		ft_putendl_fd(cmd->content, fd);
		cmd = cmd->prev;
	}
	close(fd);
}
