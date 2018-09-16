# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/27 15:32:02 by dhojt             #+#    #+#              #
#    Updated: 2018/05/14 03:35:58 by dhojt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_printf.a

COMP =			gcc -Wall -Werror -Wextra $(INCLUDES) -c -o

OBJ_DIR =		obj/
SRC_DIR =		srcs/
INCLUDES =		-I ../../includes/


SRC =			ft_printf.c \
				treatment.c \
				initialize.c \
				reinitialize.c \
				parser.c \
				parse_convert.c \
				parse_field_width.c \
				parse_precision.c \
				parse_arguments.c \
				parse_specifier.c \
				switch_display.c \
				display_d.c \
				display_c.c \
				display_s.c \
				display_u.c \
				display_x.c \
				display_o.c \
				display_p.c \
				display_ws.c \
				display_gap.c \
				display_wchar.c \
				display_other.c

OBJ =			$(SRC:%.c=%.o)

SRC_PATH =     	$(SRC:%=$(SRC_DIR)%)

OBJ_PATH =		$(addprefix $(OBJ_DIR), $(OBJ))

all:			colour $(OBJ_DIR) $(NAME) 
	@echo "\\n"FT_PRINTF COMPLETE"\\n"

colour:
	@echo "\x1b[36m""\x1b[1A\x1b[M"
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo Create: Object directory

$(NAME): $(OBJ_PATH)
	@echo Create: ft_printf.a"\x1b[1A\x1b[M"
	@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OBJ))
	@ranlib $(NAME)

$(OBJ_PATH): $(SRC_PATH)
	@$(MAKE) $(OBJ)

$(OBJ):
	@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
	@$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:			colour
	@/bin/rm -rf $(OBJ_DIR)
	@echo Cleaned ft_printf object files

fclean:			clean
	@/bin/rm -f $(NAME)
	@echo Cleaned $(NAME)

re: 			fclean all

.PHONY:			all clean flcean re colour
