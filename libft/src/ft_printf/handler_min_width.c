/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_min_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 14:43:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_arg	*wild_card_handling(va_list ap, t_arg *args, char **fmt)
{
	int		wildcard;

	wildcard = va_arg(ap, int);
	if (wildcard > 0)
		args->min_width = wildcard + 1;
	else if (args->flag && wildcard == 0)
		args->flag[F_ZERO] = TRUE;
	else
	{
		if (args->flag)
			args->flag[F_DASH] = TRUE;
		args->min_width = wildcard * (-1) + 1;
	}
	(*fmt)++;
	return (args);
}

t_arg			*handle_min_width(va_list ap, t_arg *args, char **fmt)
{
	size_t	i;

	i = 1;
	if (**fmt == '*')
		return (wild_card_handling(ap, args, fmt));
	if (ft_isdigit(**fmt))
		args->min_width = 0;
	while (ft_isdigit(**fmt))
	{
		args->min_width = args->min_width * i + *((*fmt)++) - 48;
		i *= 10;
	}
	if (args->min_width != -1)
		args->min_width++;
	return (args);
}
