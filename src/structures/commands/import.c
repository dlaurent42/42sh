/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:38:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 15:57:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	command_import_error(int fd, char *path)
{
	(path) ? remove(path) : 0;
	(path) ? ft_strdel(&path) : 0;
	(fd != -1) ? close(fd) : 0;
}

static char	command_key_verified(int fd)
{
	char	line[33];

	if (read(fd, line, 33) != 33)
		return (FALSE);
	line[32] = '\0';
	if (ft_strcmps(line, VERIF_KEY))
		return (FALSE);
	return (TRUE);
}

static char	command_parse_and_add(t_shell *sh, char *content)
{
	int		id;
	int		id_len;
	t_cmd	*new;

	if ((id = ft_atoi(content)) == 0)
		return (FALSE);
	id_len = str_size_base(10, id);
	if (ft_strlens(content + id_len + 1) > ARG_MAX)
		return (FALSE);
	if ((unsigned char)content[id_len] != ':'
	|| (unsigned char)content[id_len + 1] == 0)
		return (FALSE);
	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return (FALSE);
	new->id = id;
	ft_strcpy(new->content, &content[id_len + 1]);
	new->display_len = ft_strlenu(new->content);
	new->unicode_len = ft_strlens(new->content);
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
	return (TRUE);
}

void		command_import(t_shell *sh)
{
	int		fd;
	char	*path;
	char	*buffer;

	buffer = NULL;
	if (!(path = env_search(sh->env, "HOME")))
		return ;
	if (!(path = ft_strjoins(path, "/.cmd_history")))
		return ;
	if ((fd = open(path, O_RDONLY)) == -1 || !command_key_verified(fd))
		return (command_import_error(fd, path));
	while (get_next_line(fd, &buffer) == 1)
	{
		if (command_parse_and_add(sh, buffer) == 0)
		{
			ft_strdel(&buffer);
			return (command_import_error(fd, path));
		}
		sh->hist = ft_strjoinf(sh->hist, buffer, 3);
		sh->hist = ft_strjoinf(sh->hist, "\n", 1);
	}
	ft_strdel(&path);
	close(fd);
}
