/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:28:46 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 21:26:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_history_option_d(t_shell *sh, int *i, int *j, char **argv)
{
	int				k;
	char			*s;
	unsigned int	id;

	id = 0;
	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		s = argv[*i];
	}
	else
		s = argv[*i] + k;
	*j = ft_strlens(argv[*i]) - 1;
	if (!s)
		return (sh_history_error(4));
	if (!(ft_isdigit(s[0]) || s[0] == '+') || !ft_isint(s) || !sh->cmd
	|| (id = ft_atoi(s)) <= 0 || id < sh->cmd->last->id || id > sh->cmd->id)
		return (sh_history_error(5));
	command_delete_by_id(sh, id);
	return (0);
}
