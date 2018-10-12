/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 01:09:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:19:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_print_spaces(int diff)
{
	char			*spaces;

	if (diff < 1)
		return ;
	if ((spaces = (char *)malloc(sizeof(char) * (diff + 1))))
	{
		ft_memset(spaces, ' ', diff);
		spaces[diff] = '\0';
		ft_putstr(spaces);
		free(spaces);
	}
}
