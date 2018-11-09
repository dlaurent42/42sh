/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:38:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 12:19:59 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		buildin_jobs_bg(t_shell *sh, char **argv)
{
	return (buildin_jobs_launch(sh, argv, JOBS_BG));
}
