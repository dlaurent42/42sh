/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:44:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*lower_x_to_a(va_list ap, t_arg *args)
{
	unsigned int	nbr;

	nbr = 0;
	args->type = T_HEXA;
	if (args->size == 0)
	{
		nbr = va_arg(ap, unsigned int);
		args->content = ulltoa_base("0123456789abcdef", nbr);
	}
	else if (args->size == S_H)
		args = single_h_to_a(ap, args, "0123456789abcdef");
	else if (args->size == S_HH)
		args = double_h_to_a(ap, args, "0123456789abcdef");
	else if (args->size == S_L)
		args = single_l_to_a(ap, args, "0123456789abcdef");
	else if (args->size == S_LL)
		args = double_l_to_a(ap, args, "0123456789abcdef");
	else if (args->size == S_Z)
		args = single_z_to_a(ap, args, "0123456789abcdef");
	else if (args->size == S_J)
		args = single_j_to_a(ap, args, "0123456789abcdef");
	return (oux_width_flag_precision(args));
}

t_arg	*upper_x_to_a(va_list ap, t_arg *args)
{
	unsigned int	nbr;

	nbr = 0;
	args->type = T_LONG_HEXA;
	if (args->size == 0)
	{
		nbr = va_arg(ap, unsigned int);
		args->content = ulltoa_base("0123456789ABCDEF", nbr);
	}
	else if (args->size == S_H)
		args = single_h_to_a(ap, args, "0123456789ABCDEF");
	else if (args->size == S_HH)
		args = double_h_to_a(ap, args, "0123456789ABCDEF");
	else if (args->size == S_L)
		args = single_l_to_a(ap, args, "0123456789ABCDEF");
	else if (args->size == S_LL)
		args = double_l_to_a(ap, args, "0123456789ABCDEF");
	else if (args->size == S_Z)
		args = single_z_to_a(ap, args, "0123456789ABCDEF");
	else if (args->size == S_J)
		args = single_j_to_a(ap, args, "0123456789ABCDEF");
	return (oux_width_flag_precision(args));
}
