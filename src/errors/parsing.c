/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:25:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/31 21:28:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	parse_error(char *err)
{
	ft_putstr_fd("sh: parse error near `", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("'\n", 2);
	return (STATUS_ERR);
}
