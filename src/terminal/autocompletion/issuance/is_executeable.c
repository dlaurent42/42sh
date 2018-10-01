/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executeable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:58:03 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/29 13:40:12 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_is_executeable(t_args *args)
{
	int				type;

	type = args->data.type;
	if ((type & 1) == 1 || (type >> 3 & 1) == 1 || (type >> 6 & 1) == 1)
		return (true);
	return (false);
}
