/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 19:47:23 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:48:44 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	{
		ft_memdel((void **)&parent);
		return (NULL);
	}
	son[len + 1] = NULL;
	son[len] = value;
	while (len-- > 0)
		son[len] = parent[len];
	if (parent != NULL)
		ft_memdel((void **)&parent);
	return (son);
}

char	**arg_merge(char **tokens, int *blank_space)
{
	char	**new;
	char	*arg;
	int		i;

	new = NULL;
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	i = 1;
	arg = ft_strdup(*tokens);
	while (tokens[i] != NULL)
	{
		if (blank_space[i] == 1)
		{
			new = push(new, arg);
			arg = ft_strdup(tokens[i]);
		}
		else
			arg = ft_strjoinf(arg, ft_strdup(tokens[i]), 3);
		++i;
	}
	new = push(new, arg);
	return (new);
}
