/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:52:11 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 19:14:23 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	str2_sizes(char	**argv)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (argv[i])
	{
		ret += ft_strlen(argv[i]);
		if (argv[i + 1])
			ret++;
		i++;
	}
	return (ret);
}

static char	*ft_str2tostr(char **argv)
{
	int		i;
	int		x;
	int		cursor;
	char	*ret;

	if (!(ret = ft_strnew(str2_sizes(argv))))
		return (NULL);
	i = 0;
	cursor = 0;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			ret[cursor++] = argv[i][x];
			x++;
		}
		(argv[i + 1]) ? ret[cursor++] = ' ' : (0);
		i++;
	}
	return (ret);
}

int			sh_do_job(t_shell *sh, char **argv, t_env *env)
{
	int			ret;
	t_job		*job;
	t_process	*p;

	ret = STATUS_OK;
	job = job_new();
	job->notifications = sh->jc_muted;
	job->command = ft_str2tostr(argv);
	job_add(sh, job);
	p = process_new();
	p->argv = argv;
	p->env = env;
	job->first_process = p;
	job_launch(job, (sh->jc_muted == 1) ? 0 : 1);
	// Replace it with nanosleep
	usleep(2000);
	if (env_search(env, "?"))
		ret =  (ft_atoi(env_search(env, "?")));
	return (ret);
}
