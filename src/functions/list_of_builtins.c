/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:47:03 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/03 18:57:47 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Add all builtin functions below in the folowing format to
** ensure that they appear in auto completion for binaries:
** bin_gen_list_for_auto_comp(sh, bin, "echo");
** replace echo with name of builtin
*/

void				sh_add_builtins_to_auto_comp(t_shell *sh, t_bin *bin)
{
	bin_gen_list_for_auto_comp(sh, bin, "cd");
	bin_gen_list_for_auto_comp(sh, bin, "echo");
	bin_gen_list_for_auto_comp(sh, bin, "env");
	bin_gen_list_for_auto_comp(sh, bin, "exit");
	bin_gen_list_for_auto_comp(sh, bin, "history");
	bin_gen_list_for_auto_comp(sh, bin, "setenv");
	bin_gen_list_for_auto_comp(sh, bin, "unsetenv");
}