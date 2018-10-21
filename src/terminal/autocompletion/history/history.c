/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 09:05:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/21 18:27:29 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_history(t_shell *sh)
{
	bool			status;
	bool			sed_status;

	status = false;
	if ((sed_status = auto_hist_sed(sh, &status)))
		return (sed_status);
	if (status)
		return (false);
	auto_hist_double(sh, &status);
	auto_hist_number(sh, &status);
	auto_hist_name(sh, &status);
	return (status);
}
