/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:24:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:30:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_config_not_empty_line(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static bool	sh_config_key_verified(int fd)
{
	char	line[VERIF_KEY_LEN + 1];

	if (read(fd, line, VERIF_KEY_LEN + 1) != VERIF_KEY_LEN + 1)
		return (FALSE);
	line[VERIF_KEY_LEN] = '\0';
	if (ft_strcmps(line, VERIF_KEY))
		return (FALSE);
	return (TRUE);
}

static void	sh_config_add_checks(t_shell *sh, t_env *env, char *key, char *val)
{
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return ;
	env_insert(sh, env, key, sh_parse_quotes(val));
}

static bool	sh_config_parse_and_add(t_shell *sh, char *content)
{
	char	*str;
	char	*key;
	char	*value;
	char	is_alias;
	size_t	len;

	is_alias = FALSE;
	if (ft_strstartsby(content, "alias") && (is_alias = TRUE))
		str = content + 6;
	else if (ft_strstartsby(content, "export")
	|| ft_strstartsby(content, "setenv"))
		str = content + 7;
	else
		return (FALSE);
	len = ft_strlens(str);
	value = ft_strdups(ft_strchrsp(str, '='));
	key = ft_strdups(str);
	key[sh_get_equal_position(str)] = '\0';
	(is_alias)
		? sh_config_add_checks(sh, sh->alias, key, value)
		: sh_config_add_checks(sh, sh->env, key, value);
	ft_strdel(&key);
	ft_strdel(&value);
	return (TRUE);
}

void		sh_config_import(t_shell *sh)
{
	int		fd;
	char	*path;
	char	*buffer;

	buffer = NULL;
	if (!(path = env_search(sh->env, "CONFIG")))
		return ;
	if ((fd = open(path, O_RDONLY)) == -1 || !sh_config_key_verified(fd))
		return (error_import_export(fd, path));
	while (sh_gnl(sh, fd, &buffer) == 1)
	{
		if (buffer && buffer[0] != '#' && sh_config_not_empty_line(buffer))
			if (sh_config_parse_and_add(sh, buffer) == FALSE)
			{
				ft_strdel(&buffer);
				return (error_import_export(fd, path));
			}
		ft_strdel(&buffer);
	}
	close(fd);
}
