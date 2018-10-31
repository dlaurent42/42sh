/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 00:46:36 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/31 22:06:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_cd_remove_last_slash(char *param)
{
	int	len;

	if ((len = ft_strlens(param) - 1) == 0)
		return (param);
	while (len > 0 && param[len] == '/')
	{
		param[len] = '\0';
		len--;
	}
	return (param);
}

int			sh_cd_remove_troll(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] == '.' && (s[i + 1] == '\0' || s[i + 1] == '/'))
	{
		i++;
		if (s[i] && s[i] == '/')
			i++;
	}
	return (i);
}

static char	*sh_cd_remove_dot_dot(char *s, int i, int j)
{
	while (s && s[j] && s[i] && s[i + 1] && s[i + 2] && s[i + 3])
	{
		s[j] = s[i + 3];
		i++;
		j++;
	}
	while (s && s[j])
	{
		s[j] = '\0';
		j++;
	}
	return (s);
}

static char	*sh_cd_remove_dot(char *s, int i)
{
	while (s && s[i] && s[i + 1] && s[i + 2])
	{
		s[i] = s[i + 2];
		i++;
	}
	while (s && s[i])
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

char		*sh_cd_parse_path(char *s)
{
	int	i;
	int	last_slash;

	i = 0;
	last_slash = -1;
	while (s && s[i])
		if (s[i] == '/' && s[i + 1] == '.' && s[i + 2] == '.'
		&& (s[i + 3] == '/' || s[i + 3] == '\0'))
		{
			s = sh_cd_remove_dot_dot(s, i, last_slash);
			i = 0;
		}
		else if (s[i] == '/' && s[i + 1] == '.'
		&& (s[i + 2] == '/' || s[i + 2] == '\0'))
		{
			s = sh_cd_remove_dot(s, i);
			i = 0;
		}
		else if (s[i] == '/')
			last_slash = i++;
		else
			i++;
	return (s);
}
