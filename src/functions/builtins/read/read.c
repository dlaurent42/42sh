/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:50:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/14 18:45:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read one line from the standard input, (or from a file) and assign the
** word(s) to variable name(s).
**
** -----------------------------------------------------------------------------
**
** Syntax
**       read [-ers] [-p prompt] [-t timeout] [-n nchars] [-d delim] [name...]
**
** Key
**
**    -d delim
**              The first character of delim is used to terminate the input
**				line, rather than newline.
**
**    -e        If the standard input is coming from a terminal, readline is
**				used to obtain the line.
**
**    -n nchars
**              read returns after reading nchars characters rather than
**				waiting for a complete line of input.
**
**    -p prompt
**              Display prompt on standard error, without a trailing newline,
**				before attempting to read any input. The prompt is displayed
**				only if input is coming from a terminal.
**
**    -r        Backslash  does not act as an escape character.
**				The backslash is considered to be part of the line. In
**				particular, a backslash-newline pair can not be used as a
**				line continuation.
**
**    -s        Silent mode. If input is coming from a terminal, character
**				 are not echoed.
**
**    -t timeout
**              Cause read to time out and return failure if a complete line of
**				input is not read within timeout seconds.
**				This option has no effect if read is not reading input from
**              the terminal or a pipe.
**
**    -u fd     Read input from file descriptor fd.
**
** This is a BASH shell builtin.
**
** One line is read from the standard input, and the first word is assigned to
** the first name, the second word to the second name, and so on, with leftover
** words and their intervening separators assigned to the last name.
**
** If there are fewer words read from the standard input than names, the
** remaining names are assigned empty values.
**
** The characters in the value of the IFS variable are used to split
** the line into words.
**
** The backslash character `\' can be used to remove any special meaning for
** the next character read and for line continuation.
**
** If no names are supplied, the line read is assigned to the variable REPLY.
** The return code is zero, unless end-of-file is encountered or read times out.
*/

static char	sh_read_free(int *opt, char *prompt, char **vars, char res)
{
	int	i;

	i = 0;
	ft_printf("01\n");
	ft_strdel(&prompt);
	ft_printf("02\n");
	while (vars && i < READ_MAX_VAR)
	{
		ft_strdel(&vars[i]);
		i++;
	}
	ft_printf("03\n");
	(vars) ? free(vars) : 0;
	ft_printf("04\n");
	(opt) ? free(opt) : 0;
	ft_printf("05\n");
	return (res);
}

char		sh__read(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	int		*opt;
	char	res;
	char	**vars;
	char	*prompt;

	i = 0;
	prompt = NULL;
	if (!(opt = ft_memalloc(sizeof(int) * (READ_N_OPTIONS + 1))))
		return (1);
	ft_memset((void *)opt, -1, sizeof(int) * (READ_N_OPTIONS + 1));
	if (!(vars = ft_memalloc(sizeof(char *) * (READ_MAX_VAR + 1))))
		return (sh_read_free(opt, NULL, NULL, 1));
	ft_bzero((void *)vars, sizeof(char *) * (READ_MAX_VAR + 1));
	ft_printf("Read has started\n");
	if ((res = sh_read_options(argv, &i, &opt, &prompt)) != 0)
		return (sh_read_free(opt, prompt, vars, res));
	ft_printf("Read options have been catched (res = %d)\n", res);
	opt[READ_U] = (opt[READ_U] <= 2) ? 0 : opt[READ_U];
	opt[READ_D] = (opt[READ_D] == -1 || opt[READ_U] > 2) ? '\n' : opt[READ_D];
	opt[READ_E] = (opt[READ_E] != -1 && opt[READ_U] == 0) ? 0 : -1;
	(opt[READ_U] > 2 || sh->pid) ? opt[READ_T] = -1 : 0;
	if ((res = sh_read_variables(argv, &i, &vars)) != 0)
		return (sh_read_free(opt, prompt, vars, res));
	ft_printf("Read variables have been catched (res = %d)\n", res);
	(opt[READ_U] == 0) ? ft_putstr_fd(prompt, 2) : 0;
	
	
	i = -1;
	while (++i < READ_N_OPTIONS)
		ft_printf("OPTION[%d]: %d\n", i + 1, opt[i]);
	i = -1;
	while (++i < READ_MAX_VAR)
		ft_printf("VAR[%d]: %s\n", i + 1, vars[i]);
	
	res = sh_read_assign(sh, env, opt, vars);
	(opt[READ_U] == 0 && prompt) ? ft_putchar('\n') : 0;
	ft_printf("Read assignment has been performed\n");
	return (sh_read_free(opt, prompt, vars, res));
}
