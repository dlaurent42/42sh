/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:24:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 20:14:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	alias_key_verified(int fd)
{
	char	line[VERIF_KEY_LEN + 1];

	if (read(fd, line, VERIF_KEY_LEN + 1) != VERIF_KEY_LEN + 1)
		return (FALSE);
	line[VERIF_KEY_LEN] = '\0';
	if (ft_strcmps(line, VERIF_KEY))
		return (FALSE);
	return (TRUE);
}

static bool	alias_parse_and_add(t_shell *sh, char *content)
{
	char	*str;
	char	*key;
	char	*value;
	bool	is_alias;
	size_t	len;

	is_alias = FALSE;
	if (!content || content[0] == '#')
		return (TRUE);
	if (ft_strstartsby(content, "alias") && (is_alias == TRUE))
		str = content + 6;
	else if (ft_strstartsby(content, "export"))
		str = content + 7;
	else
		return (FALSE);
	len = ft_strlens(str);
	key = ft_strdups(ft_strchrsp(content, '='));
	value = ft_strdups(content);
	value[len - ft_strlens(key)] = '\0';
	(is_alias)
		? env_insert(sh, sh->alias, key, value)
		: env_insert_local(sh, sh->env, key, value);
	ft_strdel(&key);
	ft_strdel(&value);
	return (TRUE);
}

void		alias_import(t_shell *sh)
{
	int		fd;
	char	*path;
	char	*buffer;

	buffer = NULL;
	if (!(path = env_search(sh->env, "ALIASES")))
		return ;
	if ((fd = open(path, O_RDONLY)) == -1 || !alias_key_verified(fd))
		return (error_import_export(fd, path));
	while (get_next_line(fd, &buffer) == 1)
	{
		if (alias_parse_and_add(sh, buffer) == FALSE)
		{
			ft_strdel(&buffer);
			return (error_import_export(fd, path));
		}
		ft_strdel(&buffer);
	}
	close(fd);
}
