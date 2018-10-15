/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 00:19:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/15 14:30:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_read_parse_line(char *line, int read_r)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && read_r != -1)
		{
			j = i;
			while (line[j])
			{
				line[j] = line[j + 1];
				j++;
			}
		}
		else if (line[i] == '\t')
		{
			line[i] = ' ';
			i++;
		}
		else
			i++;
	}
	return (line);
}

static void	sh_delete_strings(char **split, char *str)
{
	int	i;

	i = 0;
	ft_strdel(&str);
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
}

static void	sh_read_set_concat(t_env *env, char *key, char **split)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (split[i])
	{
		value = (value) ? ft_strjoinf(value, " ", 1) : 0;
		value = ft_strjoinf(value, split[i], 1);
		i++;
	}
	env_insert_local(NULL, env, key, value);
	ft_strdel(&value);
}

char	sh_read_set(t_env *env, char **vars, char *line)
{
	int		i;
	char	**split;

	i = -1;
	if (!(split = ft_strsplit(line, ' ')))
	{
		ft_strdel(&line);
		return (sh_read_error_msg("read: cannot split line", 2));
	}
	if (!vars[0])
		env_insert_local(NULL, env, "REPLY", line);
	else
		while (++i < READ_MAX_VAR - 1)
			if (vars[i + 1] && split[i])
				env_insert_local(NULL, env, vars[i], split[i]);
			else if (vars[i + 1] == NULL && split[i])
			{
				sh_read_set_concat(env, vars[i], split + i);
				break ;
			}
			else
				while (i < READ_MAX_VAR - 1)
				{
					if (vars[i])
						env_insert_local(NULL, env, vars[i], "");
					i++;
				}
	sh_delete_strings(split, line);
	return (-99);
}
