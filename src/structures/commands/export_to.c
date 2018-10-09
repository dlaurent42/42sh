/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:56:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 22:14:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		command_export_to(t_shell *sh, char *path)
{
	int		fd;
	t_cmd	*cmd;

	if (!path && !(path = env_search(sh->local_env, "HISTFILE")))
		return ;
	remove(path);
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE)) == -1)
		return ;
	ft_putendl_fd(VERIF_KEY, fd);
	if (!sh->cmd)
		return ((void)close(fd));
	cmd = sh->cmd->last;
	while (cmd)
	{
		ft_putendl_fd(cmd->content, fd);
		cmd = cmd->prev;
	}
	close(fd);
}
