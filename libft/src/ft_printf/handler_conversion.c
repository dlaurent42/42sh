/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 12:55:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*handle_conversion_part_two(va_list ap, t_arg *args, char **fmt)
{
	if (**fmt == 'c')
		args = lower_c_to_a(ap, args);
	else if (**fmt == 'C')
		args = upper_c_to_a(ap, args);
	else if (**fmt == '%')
		args = percent_to_a(args);
	if (args && args->type != 0)
		(*fmt)++;
	return (args);
}

t_arg	*handle_conversion_part_one(va_list ap, t_arg *args, char **fmt)
{
	if (**fmt == 's')
		args = lower_s_to_a(ap, args);
	else if (**fmt == 'S')
		args = upper_s_to_a(ap, args);
	else if (**fmt == 'p')
		args = lower_p_to_a(ap, args);
	else if (**fmt == 'd' || **fmt == 'i')
		args = lower_d_to_a(ap, args);
	else if (**fmt == 'D')
		args = upper_d_to_a(ap, args);
	else if (**fmt == 'o')
		args = lower_o_to_a(ap, args);
	else if (**fmt == 'O')
		args = upper_o_to_a(ap, args);
	else if (**fmt == 'u')
		args = lower_u_to_a(ap, args);
	else if (**fmt == 'U')
		args = upper_u_to_a(ap, args);
	else if (**fmt == 'x')
		args = lower_x_to_a(ap, args);
	else if (**fmt == 'X')
		args = upper_x_to_a(ap, args);
	if (args && args->type != 0)
		(*fmt)++;
	return (args);
}

t_arg	*handle_conversion(va_list ap, t_arg *args, char **fmt)
{
	args = handle_conversion_part_one(ap, args, fmt);
	if (args && args->type == 0)
		args = handle_conversion_part_two(ap, args, fmt);
	if (args && args->type == 0)
		args->content = ft_strdup("%");
	return (args);
}
