/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 00:19:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/14 18:25:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_read_parse_line(char *line, int read_r)
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

static void	sh_read_set_concat(t_shell *sh, t_env *env, char *key, char **split)
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
	env_insert_local(sh, env, key, value);
	ft_strdel(&value);
}

static char	sh_read_set(t_shell *sh, t_env *env, char **vars, char *line)
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
		env_insert_local(sh, env, "REPLY", line);
	else
		while (++i < READ_MAX_VAR - 1)
			if (vars[i + 1] && split[i])
				env_insert_local(sh, env, vars[i], split[i]);
			else if (vars[i + 1] == NULL && split[i])
			{
				sh_read_set_concat(sh, env, vars[i], split + i);
				break ;
			}
	sh_delete_strings(split, line);
	return (0);
}

char		sh_read_assign(t_shell *sh, t_env *env, int *opt, char **vars)
{
	char			*line;
	char			buffer[2];
	unsigned long	timer;

	line = NULL;
	timer = (unsigned long)time(NULL) + opt[READ_T];
	ft_bzero((void *)buffer, sizeof(char) * 2);
	while ((opt[READ_T] == -1 || timer < (unsigned long)time(NULL))
	&& (read(opt[READ_U], (void *)buffer, READ_SIZE)) == READ_SIZE)
	{
		(buffer[0] == 3) ? ft_strdel(&line) : 0;
		if (buffer[0] == 3)
			return (sh_read_error_msg("^C", 2));
		if (buffer[0] == opt[READ_D] || (opt[READ_N] != -1 && --opt[READ_N]))
		{
			(opt[READ_E]) ? ft_putstr(line) : 0;
			return (sh_read_set(sh, env, vars,
			sh_read_parse_line(line, opt[READ_R])));
		}
		line = ft_strjoinf(line, buffer, 1);
		(opt[READ_S] != -1) ? ft_putchar_fd(buffer[0], 2) : 0;
		ft_bzero((void *)buffer, sizeof(char) * 2);
	}
	return (1);
}
