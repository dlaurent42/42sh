/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:19:08 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/31 20:45:20 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*execute_backtick(
				t_shell *sh, t_env *env, t_bin *bin, t_lexer lexer)
{
	char		*ret;

	ret = NULL;

	(void)sh;
	(void)env;
	(void)bin;
	(void)lexer;
	return (ret);
}
