/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executeable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:58:03 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:58:26 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_is_executeable(t_obj *obj)
{
	int				type;

	type = obj->data.type;
	if ((type & 1) == 1 || (type >> 3 & 1) == 1 || (type >> 6 & 1) == 1)
		return (true);
	return (false);
}
