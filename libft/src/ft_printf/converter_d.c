/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:49:49 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*lower_d_to_a(va_list ap, t_arg *args)
{
	int	nbr;

	nbr = 0;
	args->type = T_SIGNED_INT;
	if (args->size == 0)
	{
		nbr = va_arg(ap, int);
		args->content = lltoa_base("0123456789", nbr);
	}
	else if (args->size == S_H)
		args = single_h_to_a(ap, args, "0123456789");
	else if (args->size == S_HH)
		args = double_h_to_a(ap, args, "0123456789");
	else if (args->size == S_L)
		args = single_l_to_a(ap, args, "0123456789");
	else if (args->size == S_LL)
		args = double_l_to_a(ap, args, "0123456789");
	else if (args->size == S_Z)
		args = single_z_to_a(ap, args, "0123456789");
	else if (args->size == S_J)
		args = single_j_to_a(ap, args, "0123456789");
	return (id_width_flag_precision(args));
}

t_arg	*upper_d_to_a(va_list ap, t_arg *args)
{
	long int	nbr;

	nbr = 0;
	args->type = T_LONG_SIGNED_INT;
	if (args->size == 0)
	{
		nbr = va_arg(ap, long int);
		args->content = lltoa_base("0123456789", nbr);
	}
	else if (args->size == S_L)
		args = single_l_to_a(ap, args, "0123456789");
	else
		args = single_j_to_a(ap, args, "0123456789");
	return (id_width_flag_precision(args));
}
