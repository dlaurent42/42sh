/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_prot.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 06:54:11 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:14:33 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_PROT_H
# define  AUTO_COMPLETION_PROT_H

#include "shell.h"
#include "auto_completion.h"

bool					auto_get_obj(t_shell *shell);
void					auto_free_obj(t_obj **obj);
t_obj					*auto_create_obj(void);

void					auto_issuance(t_shell *shell);
void					auto_read_dispatcher(t_shell *shell);
void					auto_clear_selection_screen(t_shell *shell);
void					auto_manage_buffer(t_shell *sh, char *new_display);
bool					auto_get_attributes(t_shell *shell);
void					auto_show_screen(t_shell *shell, t_obj *obj);
void					auto_do_ls(t_shell *shell, t_obj *obj);
void					auto_do_file_admin(t_shell *shell, t_obj *obj);
void					auto_calc_len_file_name(t_shell *shell, t_obj *obj);
void					auto_calculate_number_of_columns(t_shell *shell);
bool					auto_path(t_obj *obj, char *path, char *name);
void					auto_move_up(t_shell *shell);
void					auto_move_down(t_shell *shell);
void					auto_move_left(t_shell *shell);
void					auto_move_right(t_shell *shell);
bool					auto_is_executeable(t_obj *obj);

bool					auto_history(t_shell *shell);

void					auto_sort(t_shell *shell);
bool					auto_sort_alpha(t_shell *shell);

void					auto_file_name(t_shell *shell, t_obj *obj);
void					auto_print_spaces(int diff);
void					auto_free_ac(t_shell *shell);

#endif
