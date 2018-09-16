# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/27 15:32:02 by dhojt             #+#    #+#              #
#    Updated: 2018/09/16 12:47:09 by dhojt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			auto_completion
INCLUDES = 		../../../include
HEADER =		$(INCLUDES)/auto_completion.h
LIBFT_A =		libft.a
FT_PRINTF_A =	ft_printf.a

COMP =			gcc -g -Wall -Werror -Wextra -I $(INCLUDES) -I $(LIBFT)/includes -c -o

OBJ_DIR =		obj/
S_SRC_DIR =		srcs/sort/
I_SRC_DIR =		srcs/issuance/
D_SRC_DIR =		srcs/display/
A_SRC_DIR =		srcs/auto_completion/

LIBFT =			libft/

S_SRC =			sort.c \
				sort_alpha.c

I_SRC =			issuance.c \
				move_right.c \
				move_left.c \
				get_attributes.c \
				do_ls.c \
				path.c \
				loop_dirs.c \
				loop_valid_dir.c \
				calc_len_file_name.c \
				is_executeable.c \
				do_file_admin.c \
				calculate_number_of_columns.c

D_SRC =			display.c \
				get_diff.c \
				file_name.c \
				print_spaces.c

A_SRC =			auto_completion.c \
				free_frame.c \
				error_exit.c \
				get_args.c \
				create_args.c \
				free_args.c

S_OBJ =			$(S_SRC:%.c=%.o)
I_OBJ =			$(I_SRC:%.c=%.o)
D_OBJ =			$(D_SRC:%.c=%.o)
A_OBJ =			$(A_SRC:%.c=%.o)
OBJ =			$(S_OBJ) $(I_OBJ) $(D_OBJ) $(A_OBJ)

S_SRC_PATH =   	$(S_SRC:%=$(S_SRC_DIR)%)
I_SRC_PATH =   	$(I_SRC:%=$(I_SRC_DIR)%)
D_SRC_PATH =   	$(D_SRC:%=$(D_SRC_DIR)%)
A_SRC_PATH =   	$(A_SRC:%=$(A_SRC_DIR)%)
SRC_PATH =		$(S_SRC_PATH) $(I_SRC_PATH) $(D_SRC_PATH) $(A_SRC_PATH)

S_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(S_OBJ))
I_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(I_OBJ))
D_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(D_OBJ))
A_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(A_OBJ))
OBJ_PATH =		$(S_OBJ_PATH) $(I_OBJ_PATH) $(D_OBJ_PATH) $(A_OBJ_PATH)

all:			colour do_libft $(OBJ_DIR) $(NAME)
				@echo "\\n$(NAME) COMPLETE"

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)
				@echo Create: Object directory

$(NAME):		$(OBJ_PATH)
				@gcc $(S_OBJ_PATH) $(I_OBJ_PATH) \
				$(D_OBJ_PATH) $(A_OBJ_PATH) \
				$(LIBFT_A) $(FT_PRINTF_A) \
				-o $(NAME) -I $(INCLUDES) -I $(LIBFT)/includes

$(S_OBJ_PATH):	$(S_SRC_PATH) $(HEADER)
				@$(MAKE) $(S_OBJ)

$(I_OBJ_PATH):	$(I_SRC_PATH) $(HEADER)
				@$(MAKE) $(I_OBJ)

$(D_OBJ_PATH):	$(D_SRC_PATH) $(HEADER)
				@$(MAKE) $(D_OBJ)

$(A_OBJ_PATH):	$(A_SRC_PATH) $(HEADER)
				@$(MAKE) $(A_OBJ)

$(S_OBJ):		$(LIBFT_A) $(FT_PRINTF_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(S_SRC_DIR)$(@:%.o=%.c)
$(I_OBJ):		$(LIBFT_A) $(FT_PRINTF_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(I_SRC_DIR)$(@:%.o=%.c)
$(D_OBJ):		$(LIBFT_A) $(FT_PRINTF_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(D_SRC_DIR)$(@:%.o=%.c)
$(A_OBJ):		$(LIBFT_A) $(FT_PRINTF_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(A_SRC_DIR)$(@:%.o=%.c)

do_libft:
				@make -C $(LIBFT)
				@cp $(LIBFT)/$(LIBFT_A) .
				@cp $(LIBFT)/$(FT_PRINTF_A) .

colour:
				@echo "\x1b[36m""\x1b[1A\x1b[M"

clean:			colour
				@/bin/rm -rf $(OBJ_DIR) $(FT_PRINTF_A) $(LIBFT_A)
				@make -C $(LIBFT) clean
				@echo Cleaned libft object files

fclean:			colour
				@/bin/rm -rf $(OBJ_DIR) $(FT_PRINTF_A) $(LIBFT_A)
				@/bin/rm -f $(NAME) $(FT_PRINTF_A) $(LIBFT_A)
				@make -C $(LIBFT) fclean
				@echo Cleaned $(NAME) and object files

re: 			fclean all

.PHONY:			all clean flcean re colour do_libft
