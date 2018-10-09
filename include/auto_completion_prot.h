/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_prot.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 06:54:11 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 13:35:00 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_PROT_H
# define AUTO_COMPLETION_PROT_H

# include "shell.h"
# include "auto_completion.h"

bool					auto_get_obj(t_shell *sh);
void					auto_free_obj(t_obj **obj);
t_obj					*auto_create_obj(void);

void					auto_issuance(t_shell *sh);
void					auto_read_dispatcher(t_shell *sh);
void					auto_clear_selection_screen(t_shell *sh);
bool					auto_get_attributes(t_shell *sh);
void					auto_show_screen(t_shell *sh, t_obj *obj);
void					auto_do_ls(t_shell *sh, t_obj *obj);
void					auto_do_file_admin(t_shell *sh, t_obj *obj);
void                    auto_do_special_modes(t_shell *sh, t_obj *obj);
void					auto_calc_len_file_name(t_shell *sh, t_obj *obj);
void					auto_calculate_number_of_columns(t_shell *sh);
bool					auto_path(t_obj *obj, char *path, char *name);
void					auto_move_up(t_shell *sh);
void					auto_move_down(t_shell *sh);
void					auto_move_left(t_shell *sh);
void					auto_move_right(t_shell *sh);
bool					auto_is_executeable(t_obj *obj);

bool					auto_history(t_shell *sh);
void					auto_hist_double(t_shell *sh, bool *status);
void					auto_hist_number(t_shell *sh, bool *status);
void					auto_hist_name(t_shell *sh, bool *status);

void					auto_sort(t_shell *sh);
bool					auto_sort_alpha(t_shell *sh);

void					auto_file_name(t_shell *sh, t_obj *obj);
void					auto_print_spaces(int diff);
void					auto_free_ac(t_shell *sh);

#endif
