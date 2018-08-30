/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 19:19:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <dirent.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>

# ifndef ARG_MAX
#  define ARG_MAX 262144
# endif

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*head;
	struct s_env		*next;
}						t_env;

typedef struct			s_cmd
{
	char				cmd[ARG_MAX];
	struct s_cmd		*head;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_shell
{
	t_cmd				*cmd;
	t_env				*env;
}						t_shell;

/*
** errors
*/
void					error_malloc(t_shell *shell, t_env *env, char *name);

/*
** structures - environment
*/
void					environment_add(t_shell *shell, t_env **env, char *var);
void					free_environment(t_env *env);
void					environment_init(t_shell *shell, t_env **env, char **environ);

/*
** structures - shell
*/
void					free_shell(t_shell *shell, int full_free);
void					shell_init(t_shell **shell);

#endif
