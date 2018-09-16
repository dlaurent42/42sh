/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:54:12 by dhojt             #+#    #+#             */
/*   Updated: 2018/08/12 18:38:39 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

static void			print_format(t_tab *tab, int count)
{
	char			*format;

	format = NULL;
	if (!count || count < 0)
		return ;
	if (!(format = ft_strndup((tab->f_copy + (tab->i - count)), count)))
		exit(1);
	ft_putstr(format);
	free(format);
	format = NULL;
}

int					parser(t_tab *tab)
{
	int				count;

	count = 0;
	if (ft_strcmp(tab->f_copy, "%") == 0)
		return (0);
	while (tab->f_copy[tab->i] != '\0')
	{
		if (tab->f_copy[tab->i] == '%')
		{
			print_format(tab, count);
			reinitialize(tab);
			treatement(tab);
			count = 0;
		}
		else
		{
			count++;
			tab->len++;
		}
		tab->i++;
	}
	print_format(tab, count);
	return (tab->len);
}
