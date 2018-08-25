/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:46:47 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 19:08:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment_add(t_shell *shell, t_env **env, char *var)
{
	t_env	*new;

	if (!(new = (t_env *)ft_memalloc(sizeof(t_env))))
		error_malloc(shell, *env, "t_env");
	new->value = ft_strdups(ft_strchrsp(var, '='));
	new->key = ft_strsub(var, 0, ft_strlens(var) - ft_strlens(new->value) - 1);
	new->head = (*env) ? (*env)->head : new;
	if (*env)
		(*env)->next = new;
	*env = new;
}
