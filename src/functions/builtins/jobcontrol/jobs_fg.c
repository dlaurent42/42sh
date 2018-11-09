/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_fg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:41:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 12:20:12 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		buildin_jobs_fg(t_shell *sh, char **argv)
{
	return (buildin_jobs_launch(sh, argv, JOBS_FG));
}
