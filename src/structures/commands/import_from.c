/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_from.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 19:17:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:29:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	command_key_verified(int fd)
{
	char	line[VERIF_KEY_LEN + 1];

	if (read(fd, line, VERIF_KEY_LEN + 1) != VERIF_KEY_LEN + 1)
		return (FALSE);
	line[VERIF_KEY_LEN] = '\0';
	if (ft_strcmps(line, VERIF_KEY))
		return (FALSE);
	return (TRUE);
}

static char	command_parse_and_add(t_shell *sh, char *content)
{
	t_cmd	*new;

	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return (FALSE);
	new->id = (sh->cmd) ? sh->cmd->id + 1 : 1;
	ft_strncpy(new->content, content, ARG_MAX);
	new->display_len = ft_strlenu(new->content);
	new->unicode_len = ft_strlens(new->content);
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
	return (TRUE);
}

void		command_import_from(t_shell *sh, t_env *env, char *path)
{
	int		fd;
	char	*buffer;

	buffer = NULL;
	if (!path && !(path = env_search(env, "HISTFILE")))
		return ;
	if ((fd = open(path, O_RDONLY)) == -1 || !command_key_verified(fd))
		return ;
	while (sh_gnl(sh, fd, &buffer) == 1)
	{
		if (command_parse_and_add(sh, buffer) == 0)
		{
			ft_strdel(&buffer);
			return ;
		}
		ft_strdel(&buffer);
	}
	close(fd);
}
