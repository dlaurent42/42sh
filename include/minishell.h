/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/24 01:07:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <dirent.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>

# define ARG_MAX 262144

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_cmd
{
	char				cmd[ARG_MAX];
	struct s_cmd		*prev; // up arrow
	struct s_cmd		*next; // down arrow
}						t_cmd;

typedef struct			s_shell
{
	char				**env; // env[i]="variable=value"
	t_cmd				*last_cmd;
}						t_shell;

#endif
