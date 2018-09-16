# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/27 15:32:02 by dhojt             #+#    #+#              #
#    Updated: 2018/07/14 01:10:31 by dhojt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

COMP =			gcc -Wall -Werror -Wextra $(INCLUDES) -c -o

OBJ_DIR =		obj/
SRC_DIR =		srcs/
INCLUDES =		-I ../../includes/

SRC =			ft_atoi.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_itoa_base.c \
				ft_lstadd.c \
				ft_lstdel.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstreturn.c \
				ft_lststrsplit.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putnbrmax_fd.c \
				ft_putnbrumax_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_removeselect.c \
				ft_str_is_alpha.c \
				ft_str_is_alphanumeric.c \
				ft_str_is_lowercase.c \
				ft_str_is_numeric.c \
				ft_str_is_printable.c \
				ft_str_is_uppercase.c \
				ft_strcapitalize.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strclr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strequ.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strlowcase.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strndup.c \
				ft_strnequ.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strsplit.c \
				ft_strsplitfirst.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_strtrim.c \
				ft_strtrimselect.c \
				ft_strupcase.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_atoi_max.c \
				get_next_line.c \
				options.c

OBJ =			$(SRC:%.c=%.o)

SRC_PATH =     	$(SRC:%=$(SRC_DIR)%)

OBJ_PATH =		$(addprefix $(OBJ_DIR), $(OBJ))

all:			colour $(OBJ_DIR) $(NAME) 
				@echo "\\n"LIBFT COMPLETE"\\n"

colour:
				@echo "\x1b[36m""\x1b[1A\x1b[M"
$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)
				@echo Create: Object directory

$(NAME): $(OBJ_PATH)
				@echo Create: libft.a"\x1b[1A\x1b[M"
				@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OBJ))
				@ranlib $(NAME)

$(OBJ_PATH): $(SRC_PATH)
				@$(MAKE) $(OBJ)

$(OBJ):
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:			colour
				@/bin/rm -rf $(OBJ_DIR)
				@echo Cleaned libft object files

fclean:			clean
				@/bin/rm -f $(NAME)
				@echo Cleaned $(NAME)

re: 			fclean all

.PHONY:			all clean flcean re colour
