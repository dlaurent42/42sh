/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_arg_size_pt_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:14:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*single_j_to_a(va_list ap, t_arg *args, char *base)
{
	intmax_t	nbr;
	uintmax_t	unbr;

	nbr = 0;
	unbr = 0;
	if (args->type == T_SIGNED_INT || args->type == T_LONG_SIGNED_INT)
	{
		nbr = va_arg(ap, intmax_t);
		args->content = lltoa_base(base, nbr);
	}
	else
	{
		unbr = va_arg(ap, uintmax_t);
		args->content = ulltoa_base(base, unbr);
	}
	return (args);
}
