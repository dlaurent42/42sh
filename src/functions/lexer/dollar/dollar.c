/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:59:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/23 20:23:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_dollar_expansion(char *str, t_env *env)
{
	char	*expanded;
	char	*result;

	expanded = NULL;
	if (!str || str[0] != '$' || !str[1] || !env)
		return (str);
	expanded = (str[1] == '{')
		? ft_strsub(str, 2, ft_strlens(str) - 3)
		: ft_strdups(str + 1);
	result = ft_strdups(env_search(env, expanded));
	ft_strdel(&expanded);
	if (!result)
		return (str);
	ft_strdel(&str);
	return (result);
}
