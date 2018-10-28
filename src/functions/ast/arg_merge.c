/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 19:47:23 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/28 21:10:32 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_deltab(void *content)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char**)content;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

int     ft_tablen(char **str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] != NULL)
			++i;
	return (i);
}

char    **push(char **parent, char *value)
{
	char    **son;
	int     len;

	len = ft_tablen(parent);
	if ((son = (char **)malloc(sizeof(char *) * (len + 2))) == NULL)
		return (NULL);
	son[len + 1] = NULL;
	son[len] = value;
	while (len-- > 0)
		son[len] = parent[len];
	ft_memdel((void **)&parent);
	return (son);
}

char    **arg_merge(char **tokens, int *blank_space)
{
	char    **new;
	char    *arg;
	int     i;

	i = 0;
	new = NULL;
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	arg = strdup(tokens[i]);
	while (tokens[++i] != NULL)
	{
		if (blank_space[i] == 1)
		{
			new = push(new, arg);
			arg = ft_strdup(tokens[i]);
		}
		else
			arg = ft_strjoinf(arg, ft_strdup(tokens[i]), 3);
	}
	new = push(new, arg);
	return (new);
}
