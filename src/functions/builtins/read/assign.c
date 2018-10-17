/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 00:19:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 15:35:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_read_parse_line(char *line, int read_r)
{
	int	i;
	int	j;

	i = 0;
	while (line && line[i])
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

static void	sh_delete_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	(split) ? free(split) : 0;
}

static void	sh_read_check_for_insert(t_env *env, char *key, char *value)
{
	if (env_search(env, key) || env->count + 1 < env->size)
		env_insert_local(NULL, env, key, value);
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
	sh_read_check_for_insert(env, key, value);
	ft_strdel(&value);
}

char		sh_read_set(t_env *env, char **vars, char *line)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_strsplit(line, ' ');
	if (!vars[0])
		sh_read_check_for_insert(env, "REPLY", line);
	else
		while (++i < READ_MAX_VAR - 1)
			if (vars[i + 1] && split && split[i])
				sh_read_check_for_insert(env, vars[i], split[i]);
			else if (vars[i + 1] == NULL && split && split[i])
			{
				sh_read_set_concat(env, vars[i], split + i);
				break ;
			}
			else
				while (i < READ_MAX_VAR - 1)
				{
					if (vars[i])
						sh_read_check_for_insert(env, vars[i], "");
					i++;
				}
	sh_delete_split(split);
	return (-99);
}
