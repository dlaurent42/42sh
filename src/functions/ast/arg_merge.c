/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 19:47:23 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/28 20:06:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_deltab(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		free(content[i++]);
	free(content);
}

int		ft_tablen(char **str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] != NULL)
			++i;
	return (i);
}

char	**push(char **parent, char *value)
{
	char	**son;
	int		len;

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

char	**arg_merge(char **tokens, int *blank_space)
{
	char	**new;
	char	*actual;
	int		i;

	i = 0;
	new = NULL;
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	actual = ft_strdup(tokens[i]);
	while (tokens[++i] != NULL)
	{
		if (blank_space[i] == 0)
			actual = ft_strjoinf(actual, tokens[i], 1);
		else
		{
			if (actual != NULL)
				new = push(new, actual);
			else
				new = push(new, ft_strdup(tokens[i]));
			actual = NULL;
		}
	}
	ft_deltab(tokens);
	return (new);
}
