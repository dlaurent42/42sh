/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:19:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 16:19:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_initialize(t_shell *shell, t_env *env, char **environ)
{
	// char		*left;
	// char		*right;
	// size_t		i;

	// i = 0;
	// left = NULL;
	// right = NULL;
	// while (environ[i])
	// {
	// 	right = ft_strchrsp(environ[i], '=');
	// 	left = ft_strsub(environ[i], 0, ft_strlens(environ[i]) - ft_strlens(right) - 1);
	// 	env_insert(shell, env, left, right);
	// 	if (left)
	// 		ft_strdel(&left);
	// 	i++;
	// }
}
