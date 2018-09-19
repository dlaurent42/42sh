/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:55:49 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 20:14:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		error_no_path_var(t_shell *sh)
{
	(sh) ? sh_delete(sh) : 0;
	ft_putendl_fd("PATH variable is unset", 2);
	exit(EXIT_FAILURE);
}
