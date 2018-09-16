/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executeable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:58:03 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/14 23:54:09 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

bool				is_executeable(t_args *args)
{
	int				type;

	type = args->data.type;
	if ((type & 1) == 1 || (type >> 3 & 1) == 1 || (type >> 6 & 1) == 1)
		return (true);
	return (false);
}
