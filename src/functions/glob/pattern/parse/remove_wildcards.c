/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:31:55 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/21 18:39:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*glob_remove_wildcars(char *str)
{
	int		i;

	i = 0;
	ft_printf("... glob_remove_wildcars received: [%s]\n", str);
	while (str[i])
	{
		if (str[i] == '*' && str[i + 1] == '*'
		&& !glob_is_in_range(str, i) && i && str[i - 1] != '/')
			sh_glob_repatriate(str, i, 1);
		else if (str[i] == '*' && str[i + 1] == '*'
		&& !glob_is_in_range(str, i) && (str[i + 2] && str[i + 2] != '/'))
			sh_glob_repatriate(str, i, 1);
		else
			i++;
	}
	ft_printf("... glob_remove_wildcars returned: [%s]\n", str);
	return (str);
}
