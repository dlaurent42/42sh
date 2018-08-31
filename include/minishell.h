/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 16:18:38 by dlaurent         ###   ########.fr       */
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
#  define ARG_MAX 		262144
# endif

# define ENV_MAX_SIZE	999
# define ENV_PRIME_1	3
# define ENV_PRIME_2	13

# define BIN_MAX_SIZE	999
# define BIN_PRIME_1	3
# define BIN_PRIME_2	13

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

typedef struct			s_bin_obj
{
	char				*name;
	char				path[PATH_MAX + 1];
	t_stat				stats;
}						t_bin_obj;

typedef struct			s_bin_item
{
	char				*key;
	char				*value;
	t_bin_obj			*obj;
}						t_bin_item;

typedef struct			s_bin
{
	size_t				size;
	size_t				count;
	t_bin_item			**items;
}						t_bin;

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
** structures - binaries
*/
int 					bin_get_hash(const char *s, const int num_buckets, const int attempt);
void					bin_delete_specified_item(t_bin_item *item);
void					bin_delete_item(t_bin *bin, const char *key);
void 					bin_delete(t_bin *bin);
void 					bin_insert(t_shell *shell, t_bin *bin, char *k, char *v);
t_bin					*bin_new(t_shell *shell);
t_bin_obj				*bin_search(t_bin *bin, const char *key);


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
