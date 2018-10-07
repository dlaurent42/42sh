/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ac.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:44:38 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 00:47:32 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_free_ac(t_shell *shell)
{
	auto_free_obj(&shell->ac->obj);
	free(shell->ac->argv);
	free(shell->ac->file_name);
	free(shell->ac->pre_file_name);
	free(shell->ac);
	shell->ac = NULL;
}
