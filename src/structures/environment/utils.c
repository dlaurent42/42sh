/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:37:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 18:37:49 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		env_is_public(t_env *env, char *str)
{
	bool	public;
	char	*key;
	size_t	len;

	key = ft_strdups(str);
	if (ft_strcountif(str, '='))
	{
		len = ft_strlens(str) - ft_strlens(ft_strchrs(str, '='));
		key[len] = '\0';
	}
	ft_printf("Received str is [%s] so key is [%s]\n", str, key);
	public = (env_search_public(env, key) == NULL) ? FALSE : TRUE;
	ft_strdel(&key);
	return (public);
}

bool		env_is_local(t_env *env, char *str)
{
	return (!env_is_public(env, str));
}
