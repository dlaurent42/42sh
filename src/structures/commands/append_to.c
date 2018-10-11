/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:56:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 12:55:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	command_append_to_new_file(t_shell *sh, t_env *env, char *path)
{
	int		fd;
	t_cmd	*cmd;

	if (!path && !(path = env_search(env, "HISTFILE")))
		return ;
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE)) == -1)
		return ;
	ft_putendl_fd(VERIF_KEY, fd);
	if (!sh->cmd)
		return ((void)close(fd));
	cmd = sh->cmd->last;
	while (cmd)
	{
		if (cmd->is_new)
			ft_putendl_fd(cmd->content, fd);
		cmd = cmd->prev;
	}
	close(fd);
}

void		command_append_to(t_shell *sh, t_env *env, char *path)
{
	int		fd;
	t_cmd	*cmd;

	if (!path && !(path = env_search(env, "HISTFILE")))
		return ;
	if ((fd = open(path, O_RDWR | O_APPEND, S_IRUSR | S_IWRITE)) == -1)
		return (command_append_to_new_file(sh, env, path));
	if (!sh->cmd)
		return ((void)close(fd));
	cmd = sh->cmd->last;
	while (cmd)
	{
		if (cmd->is_new)
			ft_putendl_fd(cmd->content, fd);
		cmd = cmd->prev;
	}
	close(fd);
}
