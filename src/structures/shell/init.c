/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:31:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 18:56:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_init(t_shell **shell)
{
	if (!(*shell = (t_shell *)ft_memalloc(sizeof(t_shell))))
		error_malloc(NULL, NULL, "t_shell");
}
