/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 00:07:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 16:29:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_read_valid_var(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char		sh_read_variables(char **argv, int *i, char ***vars)
{
	int	j;

	j = 0;
	while (argv[*i])
	{
		if (!sh_read_valid_var(argv[*i]))
			return (sh_read_error_msg(argv[*i], 1));
		if (j >= READ_MAX_VAR)
			return (0);
		(*vars)[j] = ft_strdups(argv[*i]);
		*i = *i + 1;
		j++;
	}
	return (0);
}
