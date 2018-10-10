/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:08:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 23:14:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** implementation
** 		if (no arg) : call env (+ add local var ?)
**		if (arg format "x")
**			check if key corresponds to a local variable
**				local variable : call setenv
**				!local var: add key with empty value
**		OPTIONS ??
*/

char		sh_export(t_shell $sh, char **argv)
{

}
