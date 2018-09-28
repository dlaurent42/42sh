/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:07:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 23:18:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_cd_parse_options(char **options)
{
	int	i;

	i = 0;
	if (!options)
		return (0);
	while (options[i])
	{
		if (ft_strcmps(options[i], "-P") == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
