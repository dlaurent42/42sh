/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/30 21:02:25 by dlaurent         ###   ########.fr       */
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

# define ENV_MAX_SIZE		99
# define ENV_PRIME_1		3
# define ENV_PRIME_2		13

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_env_item
{
	char				*key;
	char				*value;
}						t_env_item;

typedef struct			s_env
{
	size_t				size;
	size_t				count;
	t_env_item			**items;
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
int 					env_get_hash(const char *s, const int num_buckets, const int attempt);
void					env_delete_specified_item(t_env_item *item);
void					env_delete_item(t_env *env, const char *key);
void 					env_delete(t_env* env);
void 					env_insert(t_shell *shell, t_env *env, char *key, char *value);
void					env_initialize(t_shell *shell, t_env *env, char **environ);
char					*env_search(t_env *env, const char *key);
t_env					*env_new(t_shell *shell);

/*
** structures - shell
*/
void					shell_delete(t_shell *shell);
t_shell					*shell_new(void);

#endif
