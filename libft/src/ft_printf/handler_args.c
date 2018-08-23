/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:38 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 14:48:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*flags_initialize(void)
{
	int		i;
	int		*flags;

	i = 0;
	if (!(flags = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	while (i < 5)
	{
		flags[i] = 0;
		i++;
	}
	return (flags);
}

t_arg	*add_node(t_arg *args)
{
	t_arg	*new_arg;

	if (args)
		while (args->next)
			args = args->next;
	if (!(new_arg = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new_arg->len = 0;
	new_arg->min_width = -1;
	new_arg->precision = -1;
	new_arg->size = 0;
	new_arg->type = 0;
	new_arg->content = NULL;
	new_arg->first = NULL;
	new_arg->next = NULL;
	if (args)
	{
		args->next = new_arg;
		new_arg->first = args->first;
	}
	else
		new_arg->first = new_arg;
	if (!(new_arg->flag = flags_initialize()))
		return (new_arg);
	return (new_arg);
}
