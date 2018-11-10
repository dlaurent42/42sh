.PHONY: all clean fclean re

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR = ./src/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
SRC =	ft_atoi.c\
		ft_bzero.c\
		ft_count_argv.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isint.c\
		ft_islower.c\
		ft_isnumber.c\
		ft_isprint.c\
		ft_isupper.c\
		ft_itoa.c\
		ft_lstadd.c\
		ft_lstdel.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_memalloc.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memdel.c\
		ft_memmove.c\
		ft_memset.c\
		ft_memsets.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putnbr.c\
		ft_putnbr_fd.c\
		ft_putstr.c\
		ft_putstr_fd.c\
		ft_putstr_multi.c\
		ft_realpath.c\
		ft_strcasecmp.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strchrs.c\
		ft_strchrsp.c\
		ft_strclr.c\
		ft_strcmp.c\
		ft_strcmps.c\
		ft_strcountif.c\
		ft_strcpy.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strdupf.c\
		ft_strdups.c\
		ft_strequ.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strjoinf.c\
		ft_strjoins.c\
		ft_strlcat.c\
		ft_strleft.c\
		ft_strright.c\
		ft_strlen.c\
		ft_strlens.c\
		ft_strlenu.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strncasecmp.c\
		ft_strncat.c\
		ft_strncmp.c\
		ft_strncmps.c\
		ft_strncpy.c\
		ft_strncpys.c\
		ft_strndup.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strrev.c\
		ft_strsplit.c\
		ft_strstartsby.c\
		ft_strstr.c\
		ft_strsub.c\
		ft_strtrim.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_int_min.c\
		ft_float_min.c\
		ft_long_min.c\
		ft_double_min.c\
		ft_int_max.c\
		ft_float_max.c\
		ft_long_max.c\
		ft_double_max.c\
		ft_int_average.c\
		ft_float_average.c\
		ft_long_average.c\
		ft_double_average.c\
		ft_fact.c\
		ft_pow.c\
		ft_sort_wordtab.c\
		ft_sqrt.c\
		get_next_line.c\
		match.c\
		nmatch.c\
		options.c\
		ft_str2dup.c\
		ft_deltab.c\
		ft_printf/concatenate_content.c\
		ft_printf/converter_arg_size_pt_one.c\
		ft_printf/converter_arg_size_pt_two.c\
		ft_printf/converter_c.c\
		ft_printf/converter_d.c\
		ft_printf/converter_lltoa_base.c\
		ft_printf/converter_o.c\
		ft_printf/converter_p.c\
		ft_printf/converter_percent.c\
		ft_printf/converter_s.c\
		ft_printf/converter_str_size_base.c\
		ft_printf/converter_u.c\
		ft_printf/converter_ulltoa_base.c\
		ft_printf/converter_wchar.c\
		ft_printf/converter_x.c\
		ft_printf/error.c\
		ft_printf/ft_printf.c\
		ft_printf/handler_args.c\
		ft_printf/handler_conversion.c\
		ft_printf/handler_flags.c\
		ft_printf/handler_min_width.c\
		ft_printf/handler_precision.c\
		ft_printf/handler_size.c\
		ft_printf/manipulate_id.c\
		ft_printf/manipulate_oux.c\
		ft_printf/manipulate_p.c\
		ft_printf/manipulate_s.c\
		ft_printf/parser.c

OBJ_DIR = ./obj/
OBJ_DIR_PRINTF = $(OBJ_DIR)ft_printf/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INC_DIR = ./include/
INCS = $(addprefix $(INC_DIR), $(INC))
INC = libft.h

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_PRINTF)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
