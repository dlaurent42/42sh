/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:49:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*lower_o_to_a(va_list ap, t_arg *args)
{
	unsigned int	nbr;

	nbr = 0;
	args->type = T_UNSIGNED_OCTAL;
	if (args->size == 0)
	{
		nbr = va_arg(ap, unsigned int);
		args->content = ulltoa_base("01234567", nbr);
	}
	else if (args->size == S_H)
		args = single_h_to_a(ap, args, "01234567");
	else if (args->size == S_HH)
		args = double_h_to_a(ap, args, "01234567");
	else if (args->size == S_L)
		args = single_l_to_a(ap, args, "01234567");
	else if (args->size == S_LL)
		args = double_l_to_a(ap, args, "01234567");
	else if (args->size == S_Z)
		args = single_z_to_a(ap, args, "01234567");
	else if (args->size == S_J)
		args = single_j_to_a(ap, args, "01234567");
	return (oux_width_flag_precision(args));
}

t_arg	*upper_o_to_a(va_list ap, t_arg *args)
{
	long unsigned int	nbr;

	nbr = 0;
	args->type = T_LONG_UNSIGNED_OCTAL;
	if (args->size == 0)
	{
		nbr = va_arg(ap, long unsigned int);
		args->content = ulltoa_base("01234567", nbr);
	}
	else if (args->size == S_L)
		args = single_l_to_a(ap, args, "01234567");
	else
		args = single_j_to_a(ap, args, "01234567");
	return (oux_width_flag_precision(args));
}
