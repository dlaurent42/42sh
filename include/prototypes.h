/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:03:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 15:45:15 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "shell.h"

int						main(int argc, char **argv, char **environ);

/*
** errors
*/
void					error_malloc_sh(t_shell *sh);
void					error_malloc_env(t_shell *sh, t_env *e, char *name);
void					error_malloc_bin(t_shell *sh, t_bin *b, char *name);
void					error_malloc_reader(t_shell *sh, char *name);
void					error_no_path_var(t_shell *sh);
void					error_import_export(int fd, char *path);
int						error_pipe(void);
int						error_fork(void);
char					error_execution_tree(void);
char					error_execution_file(t_shell *sh, char *filename);
char					error_file_permissions(t_shell *sh, char *filename);
char					parse_error(char *err);
char					error_subshell(void);

/*
** functions - backtick
*/
char					*execute_backtick(t_shell *sh, t_lexer lexer);
char					*backtick_prep(t_shell *sh, t_env *env, char *token);
char					*backtick_capture(int fd);

/*
** functions - builtins
*/
void					sh_add_builtins_to_auto_comp(t_shell *sh, t_bin *bin);

/*
** functions - builtins - alias
*/
char					sh_alias(t_shell *sh, t_env *env, char **argv);
char					sh_alias_add(t_shell *sh, t_env *env, char *arg);
char					sh_alias_error(char *key, char *val, int id, char *msg);

/*
** functions - builtins - cd
*/
int						sh_cd_remove_troll(char *s);
int						sh_cd_options(
							char **argv,
							bool *opt_e,
							bool *opt_l,
							bool *opt_p);
char					sh_cd(t_shell *sh, t_env *env, char **argv);
char					sh_cd_error(char *value, char *path, int err_id);
char					sh_cd_dispatch_p(
							t_shell *sh,
							t_env *env,
							char **argv,
							int i);
char					sh_cd_dispatch(
							t_shell *sh,
							t_env *env,
							char **argv,
							int i);
char					sh_cd_follow(t_shell *sh, t_env *e, char *v, char d);
char					sh_cd_nofollow(t_shell *sh, t_env *e, char *v, char *p);
char					sh_cd_nofollow_dash(
							t_shell *sh,
							t_env *env,
							char *value,
							char *path);
char					*sh_cd_parse_path(char *s);
char					*sh_cd_remove_last_slash(char *param);
char					*sh_cd_handle_cdpath(t_env *env, char *rel_path);

/*
** functions - builtins - echo
*/
char					sh_echo(t_shell *sh, t_env *env, char **argv);

/*
** functions - builtins - env
*/
char					sh_env(t_shell *sh, t_env *src, char **argv);
char					sh_env_print(t_env *env);
char					sh_env_error(
							t_env *env,
							t_bin *bin,
							char c,
							int err_id);
char					sh_env_exec(
							t_shell *sh,
							t_env *env,
							t_bin *bin,
							char **arr);

/*
** functions - builtins - exit
*/
char					sh_exit(t_shell *sh, t_env *env, char **argv);

/*
** functions - builtins - export
*/
char					sh_export(t_shell *sh, t_env *env, char **argv);
char					sh_export_add(t_shell *sh, t_env *env, char *arg);
char					sh_export_error(char *k, char *v, int id, char *msg);

/*
** functions - builtins - history
*/
char					sh_history(t_shell *sh, t_env *env, char **argv);
char					sh_history_error(int err_id);
char					sh_history_print(t_shell *sh);
char					sh_history_print_shift(t_shell *sh, int shift);
char					sh_history_options(t_shell *sh, t_env *e, char **argv);
char					sh_history_option_c(t_shell *sh, t_env *env);
char					sh_history_option_d(
							t_shell *sh,
							int *i,
							int *j,
							char **argv);
char					sh_history_option_sp(
							t_shell *sh,
							int *i,
							int *j,
							char **argv);
char					sh_history_option_warn(
							t_shell *sh,
							t_env *env,
							char *path,
							char c);

/*
** functions - builtins - jobcontrol
*/
char					buildin_jobs_bg(t_shell *sh, char **argv);
char					buildin_jobs_fg(t_shell *sh, char **argv);
char					buildin_jobs_launch(t_shell *sh, char **argv, int mode);
char					buildin_jobs(t_shell *sh, char **argv);

/*
** functions - builtins - read
*/
char					sh__read(t_shell *sh, t_env *env, char **argv);
char					sh_read_assign(
							t_shell *sh,
							t_env *env,
							int *opt,
							char **vars);
char					sh_read_error_msg(char *s, char err_id);
char					sh_read_error(char c, char err_id);
char					sh_read_options(char **av, int *i, int **opt, char **p);
char					sh_read_option_d(char **av, int *i, int *j, int **opt);
char					sh_read_option_n(char **av, int *i, int *j, int **opt);
char					sh_read_option_p(char **av, int *i, int *j, char **p);
char					sh_read_option_t(char **av, int *i, int *j, int **opt);
char					sh_read_option_u(char **av, int *i, int *j, int **opt);
char					sh_read_variables(char **av, int *i, char ***vars);
char					*sh_read_parse_line(char *line, int read_r);
char					sh_read_set(t_env *env, char **vars, char *line);
char					sh_read_loop(t_shell *s, t_env *e, int *o, char **v);
char					sh_read_timeout_loop(
							t_shell *sh,
							t_env *env,
							int *opt,
							char **vars);

/*
** functions - builtins - setenv
*/
char					sh_setenv(t_shell *sh, t_env *env, char **argv);
char					sh_setenv_add(t_shell *sh, t_env *env, char *arg);
char					sh_setenv_error(char *k, char *v, int id, char *msg);

/*
** functions - builtins - unalias
*/
char					sh_unalias(t_shell *sh, t_env *env, char **argv);
char					sh_unalias_remove(t_env *env, char *arg);
char					sh_unalias_error(char *key, int err_id);

/*
** functions - builtins - unset
*/
char					sh_unset(t_shell *sh, t_env *env, char **argv);
char					sh_unset_remove(t_env *env, char *arg);
char					sh_unset_error(char *key, int err_id);

/*
** functions - builtins - unsetenv
*/
char					sh_unsetenv(t_shell *sh, t_env *env, char **argv);
char					sh_unsetenv_remove(t_env *env, char *arg);
char					sh_unsetenv_error(char *key, int err_id);

/*
** functions - builtins - utils
*/
int						sh_get_equal_position(char *arg);
int						sh_is_binary(char *arg);
bool					sh_is_option_string(char *s, char *opt);
char					*sh_get_path_from_filename(char *filename);
char					*sh_parse_quotes(char *arg);

/*
** functions - check
*/
char					sh_command_check_lexer(t_shell *sh, t_lexer *lexer);
char					*sh_command_check(t_env *env, char *s, int type);
char					*sh_replace_aliases(t_env *alias, char *s);
/*
** char					lexer_check_brackets(char *str, char c);
*/

/*
** functions - jobs
*/
void					job_launch(t_job *job, int foreground);
void					put_job_in_foreground(t_job *job, int cont);
void					put_job_in_background(t_job *job, int cont);
void					job_wait(t_job *job);
void					job_message(t_job *job, char *status);
void					job_message_suspended(t_job *job);
void					job_notification(void);
void					job_continue(t_job *job, int foreground);
void					job_error(t_job *job, int pipe);
int						sh_do_job(t_shell *sh, char **argv, t_env *env);

/*
** functions - process
*/
void					process_launch(
							t_process *p,
							pid_t pgid,
							int fd[3],
							int foreground);
int						process_status(pid_t pid, int status);

/*
** functions - lexer - aliases
*/
char					*lexer_aliases(t_env *aliases, char *s, int start);

/*
** functions - lexer - backtick
*/
t_lexer_glob			*add_node_lexer_backtick(
							t_lexer_glob *current, char *s, int type);
size_t					backtick_splice_points(char *s);

/*
** functions - lexer - dollar
*/
char					*sh_dollar_expansion(char *str, t_env *env);
char					*lexer_expand(t_env *env, char *str, int i);

/*
** functions - lexer - glob
*/
char					*sh_glob(char *str);
void					lexer_glob(t_shell *sh, t_env *e, t_token_tree **t);
t_lexer_glob			*add_node_lexer_glob(t_lexer_glob *c, char *s, int t);

/*
** functions - lexer - glob - cbraces
*/
char					*sh_glob_cbraces(char *str);
bool					sh_glob_cbraces_check(char *str);
bool					sh_glob_cbraces_start_stop(t_cbraces *cb);
char					sh_glob_cbraces_dots(t_cbraces *cb);
void					sh_glob_cbraces_dots_expand(t_cbraces *cb);
void					sh_glob_cbraces_rp_num(t_cbraces *cb);
void					sh_glob_cbraces_rp_alpha(t_cbraces *cb);
bool					sh_glob_cbraces_list(t_cbraces *cb);
void					sh_glob_cbraces_expand(t_cbraces *cb);

/*
** functions - lexer - glob - patterns
*/
char					*sh_glob_pattern(char *str);
char					*sh_glob_expand_ranges(t_filesystem *fs, char *str);
char					*glob_remove_wildcars(char *str);
void					sh_glob_add_initial_path(t_glob *glob);
void					sh_glob_add_path(
							t_filesystem *fs,
							char *path,
							char *name);
void					sh_glob_add_result(
								t_glob *glob,
								char *path,
								char *name);
void					sh_glob_check_final_paths(
								t_glob *glob,
								t_filesystem *fs1,
								char *str);
void					sh_glob_check_paths(
								t_glob *glob,
								t_filesystem *fs1,
								char *str,
								t_filesystem *fs2);
void					sh_glob_check_all_paths(
								t_glob *glob,
								t_filesystem *fs1,
								t_filesystem *fs2);

/*
** functions - lexer - glob - utils
*/
bool					glob_match(char *s1, char *s2, char **lst);
bool					glob_in_range(char *str, int pos);
char					**cbraces_strsplit(char *s, char c);
char					**pattern_strsplit(char *s, char c);

/*
** functions - lexer - handlers
*/
bool					sh_command_parse_backslash(char *str);
bool					sh_command_empty(char *str);
bool					sh_command_quotes_check(char *str);
void					sh_command_trim(char *str);
void					sh_remove_useless_quotes(char *str);
void					sh_command_expand_tile(t_shell *sh, t_env *e, char *s);
void					sh_command_expand_dollars(
							t_shell *sh,
							t_env *env,
							char *str);

/*
** functions - lexer - heredoc
*/
char					sh_heredoc_orga(t_lexer *lexer, char status);
bool					sh_heredocs_all_close(t_shell *sh);
char					sh_heredoc(t_shell *sh, char *str);
char					sh_heredoc_add(t_shell *sh, char *heredoc);
void					sh_heredoc_delete(t_shell *sh);
char					sh_heredoc_init(t_shell *sh, char *heredoc);
char					sh_heredoc_update(t_shell *sh);
char					*sh_heredoc_get_next(t_shell *sh);

/*
** functions - lexer - tilde
*/
char					*lexer_tilde(t_env *env, char *s, int i);

/*
** functions - lexer - tokenize
*/
char					lexer_entry(t_lexer *lexer, char *cmd);
char					lexer_fill(t_lexer *lexer, char *cmd);
void					lexer_token_add(
							t_lexer *lexer,
							char *src,
							size_t size,
							t_token_type type);
char					lexer_delete(t_lexer *lexer, char status);
char					lexer_token_merge(t_lexer *lexer, size_t i);
char					lexer_handle_subshell(
							t_lexer *lexer,
							char *cmd,
							int *i,
							int *j);
char					lexer_token_singlequote(
							t_lexer *l,
							char *cmd,
							int *i,
							int *j);
char					lexer_token_doublequote(
							t_lexer *lexer,
							char *cmd,
							int *i,
							int *j);
char					lexer_token_backquote(
							t_lexer *lexer,
							char *cmd,
							int *i,
							int *j);
t_token					*lexer_token_search(char *cmd, int i);
const t_token			*lexer_lexic_singletone(void);

/*
** functions - lexer - utils
*/
void					lexer_remove_useless_quotes(char *str);
char					*lexer_backslash(char *s, int type);
void					lexer_inject_cpy(char *str, char *injection, int i);
char					*lexer_inject_dup(char *str, char *injection, int i);
bool					lexer_is_empty(char *str);
bool					lexer_is_esc(char *str, int i);
bool					lexer_is_new_cmd(char *s, int pos);
void					lexer_is_quote(char *s, int i, char *dq, char *sq);
bool					lexer_need_esc(char c);
void					lexer_repatriate(char *str, int i, int len);
int						lexer_strcountif(char *str, char c);
char					**lexer_strsplit(char *s, char c);
char					**lexer_strsplit_ws(char *s);
bool					glob_conditions(char *str);

/*
** functions - exec
*/
char					sh_command_dispatch(
							t_shell *sh,
							t_env *env,
							char **argv);

/*
** functions - parser
*/
char					**sh_command_build(char *str);
bool					sh_is_not_builtin(char *str);
void					sh_command_parser(
							t_shell *sh,
							t_env *env,
							t_bin *bin,
							char *str);
bool					sh_command_test_path(char **arg);

/*
** functions - run
*/
void					sh_command_prepare(t_shell *sh);
char					sh_command_run(
							t_shell *sh,
							t_env *env,
							t_bin *bin,
							char **str);
char					sh_command_run_lexer(
							t_shell *sh,
							t_env *env,
							t_lexer *lexer,
							char **cmd);
char					sh_command_run_tree(
							t_shell *sh,
							t_env *env,
							t_bin *bin,
							t_lexer lexer);
char					sh_command_dispatch(t_shell *sh, t_env *env, char **a);

/*
** functions - subshell
*/
int						sh_subshell(t_shell *sh, char **argv);
char					execute_subshell_env(t_env *env, char **arr);
char					execute_subshell(
									t_shell *sh,
									t_env *env,
									t_token_tree *tree);

/*
** structures - binaries
*/
long					bin_get_hash(const char *sh, const int b, const int a);
void					bin_delete_specified_item(t_bin_item *item);
void					bin_delete_item(t_bin *bin, const char *key);
void					bin_delete(t_bin *bin);
void					bin_insert(t_shell *sh, t_bin *b, t_bin_obj *obj);
void					bin_initialize(t_shell *sh, t_env *env, t_bin *bin);
void					bin_gen_list_for_auto_comp(
							t_shell *sh,
							t_bin *bin,
							char *s);
t_bin					*bin_update(t_shell *sh, t_env *env, t_bin *bin);
t_bin					*bin_new(t_shell *sh, t_env *env);
t_bin_obj				*bin_search(t_bin *bin, const char *key);
t_bin_obj				*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st);

/*
** structures - commands
*/
void					command_add(t_shell *sh, bool is_new);
void					command_add_str_based(t_shell *sh, char *s, bool isnew);
void					command_append_from(t_shell *sh, t_env *env, char *p);
void					command_append_to(t_shell *sh, t_env *env, char *p);
void					command_delete_all(t_shell *sh);
void					command_delete_by_id(t_shell *sh, unsigned int id);
void					command_import(t_shell *sh);
void					command_import_from(t_shell *sh, t_env *env, char *p);
void					command_export_all(t_shell *sh);
void					command_export_to(t_shell *sh, t_env *env, char *file);

/*
** structures - environment
*/
long					env_get_hash(const char *sh, const int b, const int a);
bool					env_key_is_ok(char *name);
bool					env_key_is_protected(char *name);
bool					env_is_public(t_env *env, char *str);
bool					env_is_local(t_env *env, char *str);
bool					env_display(t_env *env, char *keyword);
void					env_delete_specified_item(t_env_item *item);
void					env_delete_item(t_env *env, const char *key);
void					env_delete(t_env *env);
void					env_insert(t_shell *sh, t_env *env, char *k, char *v);
void					env_insert_local(
							t_shell *sh,
							t_env *e,
							char *k,
							char *v);
void					env_insert_protected(
							t_shell *sh,
							t_env *env,
							char *k,
							char *v);
void					env_initialize(t_shell *sh, t_env *env, char **e);
void					env_initialize_local(t_shell *sh, char *name);
void					sh_env_init_config(t_shell *sh);
void					sh_env_init_histfile(t_shell *sh);
void					sh_env_init_home(t_shell *sh);
void					sh_env_init_ppid(t_shell *sh);
void					sh_env_init_ps(t_shell *sh);
void					sh_env_init_pwd(t_shell *sh);
void					sh_env_init_shell(t_shell *sh, char *path);
void					sh_env_init_shlvl(t_shell *sh);
void					sh_env_init_specials(t_shell *sh, char *name);
void					sh_env_init_term(t_shell *sh);
void					env_local_to_public(t_env *env, char *key, char *value);
void					env_insert_item_into_array(t_env *e, char *k, char *v);
void					env_delete_autocompletion_array(t_env *env);
void					env_search_autocompletion(t_shell *sh, char *key);
char					*env_search(t_env *env, const char *key);
char					*env_search_public(t_env *env, const char *key);
char					*env_search_local(t_env *env, const char *key);
char					env_delete_item_from_array(t_env *env, const char *key);
t_env					*env_new(t_shell *sh, char **environ);
t_env					*env_copy(t_shell *sh, t_env *src);

/*
** structures - gnl
*/
int						sh_gnl(t_shell *sh, int const fd, char **line);
void					gnl_delete(t_shell *sh);

/*
** structures - jobs
*/
void					job_destroy_all(t_job *job);
t_job					*job_new(int muted, char **argv);
int						job_is_completed(t_job *job);
int						job_is_stopped(t_job *job);
void					job_delete(t_job *job);
void					job_add(t_shell *sh, t_job *new);
t_job					*job_get_by_id(t_job *job, int id);
int						job_get_max_id(t_job *job);

/*
** structures - reader
*/
void					read_delete(t_read *read);
t_read					*read_new(t_shell *sh);

/*
** structures - shell
*/
void					sh_config_import(t_shell *sh);
void					sh_delete(t_shell *sh);
void					sh_set_prompt(t_shell *sh);
char					sh_set_termios(t_shell *sh);
void					sh_unset_termios(t_shell *sh);
char					*sh_get_folder_name(t_env *e, char *l, size_t len);
char					*sh_get_git_branch(t_shell *sh, char *location);
t_shell					*sh_new(int argc, char **argv, char **environ);
t_exec					*sh_init_exec(t_env *env, t_bin *bin);
void					sh_destroy_exec(t_exec **exec);
void					jobs_display(t_job *job);

/*
** structures - process
*/
bool					process_add(t_shell *sh, pid_t pid);
bool					process_destroy(t_shell *sh, t_process *process);
bool					process_destroy_all(t_shell *sh);
bool					process_destroy_pid(t_shell *sh, pid_t pid);
void					process_display(t_process *process);
t_process				*process_get(t_shell *sh, pid_t pid);
t_process				*process_get_pid(t_shell *sh, pid_t pid);
t_process				*process_new(void);

/*
** terminal - auto_completion
*/
bool					auto_completion(t_shell *sh);
void					auto_display(t_shell *sh, t_obj *obj, bool first_print);
bool					auto_get_obj(t_shell *sh);
void					auto_free_obj(t_obj **obj);
t_obj					*auto_create_obj(void);

void					auto_issuance(t_shell *sh);
void					auto_read_dispatcher(t_shell *sh);
void					auto_clear_selection_screen(t_shell *sh);
bool					auto_get_attributes(t_shell *sh);
void					auto_show_screen(t_shell *sh, t_obj *obj);
void					auto_merge_objs(t_shell *sh, t_obj *obj);
void					auto_do_ls(t_shell *sh, t_obj *obj);
void					auto_do_file_admin(t_shell *sh, t_obj *obj);
void					auto_do_special_modes(t_shell *sh, t_obj *obj);
void					auto_calc_len_file_name(t_shell *sh, t_obj *obj);
void					auto_calculate_number_of_columns(t_shell *sh);
bool					auto_path(t_obj *obj, char *path, char *name);
void					auto_move_up(t_shell *sh);
void					auto_move_down(t_shell *sh);
void					auto_move_left(t_shell *sh);
void					auto_move_right(t_shell *sh);
bool					auto_is_executeable(t_obj *obj);
char					*auto_get_escaped_str(char *str);
bool					contains_printable_characters(char *str);
char					*move_past_leading_spaces(char *content);

bool					auto_env(t_shell *sh);

bool					auto_history(t_shell *sh);
void					auto_hist_double(t_shell *sh, bool *status);
void					auto_hist_question(t_shell *sh, bool *status);
void					auto_hist_number(t_shell *sh, bool *status);
void					auto_hist_name(t_shell *sh, bool *status);
bool					auto_hist_sed(t_shell *sh, bool *status);
void					auto_hist_new_prompt(t_shell *sh, bool *status);

bool					auto_glob(t_shell *sh);

void					auto_sort(t_obj *obj);

void					auto_file_name(t_shell *sh, t_obj *obj);
void					auto_print_spaces(int diff);
void					auto_free_ac(t_shell *sh);

/*
** terminal - cursor
*/
void					sh_move_home(t_shell *sh);
void					sh_move_end(t_shell *sh);
void					sh_move_left(t_shell *sh);
void					sh_move_right(t_shell *sh);
void					sh_move_up(t_shell *sh);
void					sh_move_down(t_shell *sh);
void					sh_move_y(t_shell *sh, int y);
void					sh_move_x(t_shell *sh, int x);
void					sh_move_to_xy(t_shell *sh, int x, int y);
void					sh_move_next_word(t_shell *sh);
void					sh_move_previous_word(t_shell *sh);
void					sh_set_rel_pos(t_shell *sh, int delta, int dir);

/*
** terminal - delete
*/
void					sh_delete_char(t_shell *sh);
void					sh_delete_current_char(t_shell *sh);
void					sh_delete_all(t_shell *sh);
void					sh_delete_to_end(t_shell *sh);
void					sh_delete_from_home(t_shell *sh);
void					sh_delete_previous_word(t_shell *sh);
void					sh_delete_next_word(t_shell *sh);

/*
** terminal - history - browse
*/
void					sh_browse_next(t_shell *sh);
void					sh_browse_prev(t_shell *sh);
void					sh_browse_freeze(t_shell *sh);
char					sh_browse_compare(char *command, char *buffer);

/*
** terminal - history - search
*/
void					sh_search_freeze(t_shell *sh);
void					sh_history_search(t_shell *sh);
void					sh_history_bufferize(t_shell *sh, char *line);
void					sh_history_move_cursor(t_shell *sh);
void					sh_history_print_result(t_shell *sh);
void					sh_history_perform_search(t_shell *sh);
void					sh_search_init(t_shell *sh);

/*
** terminal - multilines
*/
void					sh_multilines(t_shell *sh, char status);
void					sh_multilines_close(t_shell *sh);

/*
** terminal - print
*/
void					sh_fill_buffer(t_shell *sh);
void					sh_print_cmd(t_shell *sh, t_cmd *cmd);
void					sh_print_prompt(t_shell *sh);
void					sh_print_str(t_shell *sh, char *str);
void					sh_welcome(void);
void					sh_select_print(t_shell *sh);

/*
** terminal - read
*/
char					sh_read(t_shell *sh);
void					sh_print_prompt(t_shell *sh);
void					sh_read_dispatcher(t_shell *sh);
void					sh_deletion_dispatcher(t_shell *sh);
char					sh_is_arrow_combination(char *s);
char					sh_is_select_combination(char *s);
char					sh_is_delete_combination(char *s);

/*
** terminal - select
*/
void					sh_cut_selection(t_shell *sh);
void					sh_copy_selection(t_shell *sh);
void					sh_paste_selection(t_shell *sh);
void					sh_select_down(t_shell *sh);
void					sh_select_left_char(t_shell *sh);
void					sh_select_left_word(t_shell *sh);
void					sh_select_right_char(t_shell *sh);
void					sh_select_right_word(t_shell *sh);
void					sh_select_end(t_shell *sh);
void					sh_select_home(t_shell *sh);
void					sh_select_up(t_shell *sh);
void					sh_unselect(t_shell *sh);
void					sh_unselect_delete(t_shell *sh, unsigned char c);
void					sh_select_set_pos(t_shell *sh);
int						sh_get_selection_len(t_shell *sh);
int						sh_get_start_rel_from_abs(t_shell *sh);

/*
** terminal - signals
*/
void					signal_catching(void);
void					sh_sigint_reset(t_shell *sh, char *last_return);
void					sh_window_resize(t_shell *sh);
void					signal_default(void);

/*
** structures - ast
*/
t_token_tree			*new_tree_node(void);
void					add_tree_node(t_token_tree **head, t_token_tree **last,
										t_token_tree *new);
int						add_tree_to_back(t_token_tree **h, t_token_tree *new);
void					clean_tree(t_token_tree *tree);
t_token_tree			*copy_tree_node(t_token_tree *obj);
t_token_tree			*get_tree_last_node(t_token_tree *list);

/*
** functions - ast
*/
t_token_tree			*build_list(t_lexer lexer);
size_t					get_tree_token_type(t_token token);
t_token_tree			*build_token_tree(t_token_tree *list);
int						execute_tree(t_shell *sh, t_token_tree *tree);
char					sh_command_run_ast(t_shell *sh, t_env *env, t_bin *bin,
														t_token_tree *tree);
int						reorganise_tokens(t_token_tree **list);
void					reorganise_command(t_token_tree *curent_command);
void					reorganise_and_or(t_token_tree *curent_command);
bool					squash_type_zero(t_token_tree *current_command);
char					**arg_merge(char **tokens, int *blank_space);

/*
** functions - ast - operators
*/
char					execute_semicolon(t_shell *sh, t_token_tree *tree);
char					execute_conditions(t_shell *sh, t_token_tree *tree);
char					execute_pipe(t_shell *sh, t_token_tree *tree);
char					execute_left_redirection(t_shell *sh,
													t_token_tree *tree);
char					execute_right_redirection(t_shell *sh,
													t_token_tree *tree);
char					left_heredoc(
							t_shell *sh, t_token_tree *tree, int count);
char					execute_fd_aggr(t_shell *sh, t_token_tree *tree);
char					*get_front_descriptor(char *cmd, size_t len,
													int closed);
char					*get_back_descriptor(char *cmd);
char					error_file_descriptor(char **back);

#endif
