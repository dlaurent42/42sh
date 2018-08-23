/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*lower_p_to_a(va_list ap, t_arg *args)
{
	size_t	nbr;

	args->type = T_POINTER;
	nbr = (size_t)va_arg(ap, void *);
	if (nbr == 0)
	{
		args->content = ft_strdup("0x0");
	}
	else
	{
		args->content = ulltoa_base("0123456789abcdef", nbr);
		args->content = ft_strjoinf("0x", args->content, 2);
	}
	return (p_width_flag(args));
}
