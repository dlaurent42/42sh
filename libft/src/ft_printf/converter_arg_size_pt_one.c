/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_arg_size_pt_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:14:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*single_h_to_a(va_list ap, t_arg *args, char *base)
{
	short			nbr;
	unsigned short	unbr;

	nbr = 0;
	unbr = 0;
	if (args->type == T_SIGNED_INT || args->type == T_LONG_SIGNED_INT)
	{
		nbr = (short)va_arg(ap, int);
		args->content = lltoa_base(base, nbr);
	}
	else
	{
		unbr = (unsigned short)va_arg(ap, unsigned int);
		args->content = ulltoa_base(base, unbr);
	}
	return (args);
}

t_arg	*double_h_to_a(va_list ap, t_arg *args, char *base)
{
	char			nbr;
	unsigned char	unbr;

	nbr = 0;
	unbr = 0;
	if (args->type == T_SIGNED_INT || args->type == T_LONG_SIGNED_INT)
	{
		nbr = (char)va_arg(ap, int);
		args->content = lltoa_base(base, nbr);
	}
	else
	{
		unbr = (unsigned char)va_arg(ap, unsigned int);
		args->content = ulltoa_base(base, unbr);
	}
	return (args);
}

t_arg	*single_l_to_a(va_list ap, t_arg *args, char *base)
{
	long			nbr;
	unsigned long	unbr;

	nbr = 0;
	unbr = 0;
	if (args->type == T_SIGNED_INT || args->type == T_LONG_SIGNED_INT)
	{
		nbr = (long)va_arg(ap, long);
		args->content = lltoa_base(base, nbr);
	}
	else
	{
		unbr = (unsigned long)va_arg(ap, unsigned long);
		args->content = ulltoa_base(base, unbr);
	}
	return (args);
}

t_arg	*double_l_to_a(va_list ap, t_arg *args, char *base)
{
	long long			nbr;
	unsigned long long	unbr;

	nbr = 0;
	unbr = 0;
	if (args->type == T_SIGNED_INT || args->type == T_LONG_SIGNED_INT)
	{
		nbr = (long long)va_arg(ap, long long);
		args->content = lltoa_base(base, nbr);
	}
	else
	{
		unbr = (unsigned long long)va_arg(ap, unsigned long long);
		args->content = ulltoa_base(base, unbr);
	}
	return (args);
}

t_arg	*single_z_to_a(va_list ap, t_arg *args, char *base)
{
	intmax_t	nbr;
	size_t		unbr;

	nbr = 0;
	unbr = 0;
	if (args->type == T_SIGNED_INT || args->type == T_LONG_SIGNED_INT)
	{
		nbr = va_arg(ap, intmax_t);
		args->content = lltoa_base(base, nbr);
	}
	else
	{
		unbr = va_arg(ap, size_t);
		args->content = ulltoa_base(base, unbr);
	}
	return (args);
}
