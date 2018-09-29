/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 17:37:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_exit(t_shell *sh, char *value)
{
	int	status;

	status = ft_atoi(value) % 256;
	status = (status < 0) ? 256 + status : status;
	sh_delete(sh);
	exit(status);
}
