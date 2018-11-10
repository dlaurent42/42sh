/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:50:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 20:48:10 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 64

# define F_PLUS 0
# define F_DASH 1
# define F_ZERO 2
# define F_SPACE 3
# define F_HASHTAG 4
# define NB_FLAGS 5
# define RL_BUFSIZE	1024

# define S_H 1
# define S_HH 2
# define S_L 3
# define S_LL 4
# define S_Z 5
# define S_J 6

# define T_STRING 1
# define T_WSTRING 2
# define T_POINTER 3
# define T_SIGNED_INT 4
# define T_LONG_SIGNED_INT 5
# define T_UNSIGNED_OCTAL 6
# define T_LONG_UNSIGNED_OCTAL 7
# define T_UNSIGNED_INT 8
# define T_LONG_UNSIGNED_INT 9
# define T_HEXA 10
# define T_LONG_HEXA 11
# define T_CHAR 12
# define T_WCHAR 13
# define T_PERCENT 99

# define TRUE 1
# define FALSE 0

# define MASK1 "110xxxxx10xxxxxx"
# define MASK2 "1110xxxx10xxxxxx10xxxxxx"
# define MASK3 "11110xxx10xxxxxx10xxxxxx10xxxxxx"

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <wchar.h>
# include <limits.h>
# include <stdbool.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_arg
{
	int				len;
	int				*flag;
	int				min_width;
	int				precision;
	int				size;
	int				type;
	char			*content;
	struct s_arg	*first;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_gnl
{
	int				fd;
	int				rr;
	int				gnl;
	char			*buff;
	char			*content;
	struct s_gnl	*head;
	struct s_gnl	*next;
}					t_gnl;

/*
** Conversions
*/
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);

/*
** Display
*/
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_putstr_multi(char *old_str, int n_times);

/*
** Memory
*/
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memsets(void *b, int c, size_t len);
size_t				ft_count_argv(void	**array);

/*
** Characters
*/
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);

/*
** Strings
*/
int					ft_strcasecmp(const char *s1, const char *s2);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strchrs(const char *s, int c);
char				*ft_strchrsp(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strcmps(const char *s1, const char *s2);
int					ft_strcountif(char *s, char c);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
char				*ft_strdupf(char *s1);
char				*ft_strdups(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinf(char *s1, char *s2, int opt);
char				*ft_strjoins(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strleft(char *src, size_t len);
char				*ft_strright(const char *src, size_t len);
size_t				ft_strlen(const char *s);
size_t				ft_strlens(const char *s);
size_t				ft_strlenu(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncasecmp(const char *s1, const char *s2, size_t len);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strncmps(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strncpys(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *s1, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strrev(char *str);
char				**ft_strsplit(char const *s, char c);
char				ft_strstartsby(char *origin, char *seek);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_sort_wordtab(char **tab);
int					match(char *s1, char *s2);
int					nmatch(char *s1, char *s2);
char				**ft_str2dup(char **arr);
void				ft_deltab(void *content);

/*
** Linked lists
*/
void				ft_lstadd(t_list **alst, t_list *new_lst);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);

/*
** Maths
*/
int					ft_isint(char *str);
int					ft_int_average(int *val);
float				ft_float_average(float *val);
long				ft_long_average(long *val);
double				ft_double_average(double *val);
int					ft_int_max(int a, int b);
float				ft_float_max(float a, float b);
long				ft_long_max(long a, long b);
double				ft_double_max(double a, double b);
int					ft_int_min(int a, int b);
float				ft_float_min(float a, float b);
long				ft_long_min(long a, long b);
double				ft_double_min(double a, double b);
int					ft_fact(int nb);
long				ft_pow(long nb, long power);
int					ft_sqrt(int nb);
int					ft_isnumber(char *str);

/*
** Get_next_line.c
*/
int					get_next_line(int const fd, char **line);

/*
** options
*/
unsigned long		options(char **argv);

/*
** sym_link
*/
bool				ft_realpath(char **path);

/*
** 	~~~~~~~~~~~~~~~~~~~~ PRINTF FUNCTIONS ~~~~~~~~~~~~~~~~~~~~ **
*/

/*
** concatenate_content.c
*/
int					concatenate_content(t_arg *args);

/*
** converter_arg_size.c (part one and two)
*/
t_arg				*single_h_to_a(va_list ap, t_arg *args, char *base);
t_arg				*double_h_to_a(va_list ap, t_arg *args, char *base);
t_arg				*single_l_to_a(va_list ap, t_arg *args, char *base);
t_arg				*double_l_to_a(va_list ap, t_arg *args, char *base);
t_arg				*single_z_to_a(va_list ap, t_arg *args, char *base);
t_arg				*single_j_to_a(va_list ap, t_arg *args, char *base);

/*
** converter_str_size_base.c
*/
size_t				str_size_base(size_t base_size, unsigned long long nbr);

/*
** converter_lltoa_base.c
*/
char				*lltoa_base(char *base, long long nbr);

/*
** converter_ulltoa_base.c
*/
char				*ulltoa_base(char *base, unsigned long long nbr);

/*
** converter_c.c
*/
t_arg				*lower_c_to_a(va_list ap, t_arg *args);
t_arg				*upper_c_to_a(va_list ap, t_arg *args);

/*
** converter_d.c
*/
t_arg				*lower_d_to_a(va_list ap, t_arg *args);
t_arg				*upper_d_to_a(va_list ap, t_arg *args);

/*
** converver_o.c
*/
t_arg				*lower_o_to_a(va_list ap, t_arg *args);
t_arg				*upper_o_to_a(va_list ap, t_arg *args);

/*
** converter_p.c
*/
t_arg				*lower_p_to_a(va_list ap, t_arg *args);

/*
** converter_percent.c
*/
t_arg				*percent_to_a(t_arg *args);

/*
** converter_s.c
*/
t_arg				*lower_s_to_a(va_list ap, t_arg *args);
t_arg				*upper_s_to_a(va_list ap, t_arg *args);

/*
** converter_u.c
*/
t_arg				*lower_u_to_a(va_list ap, t_arg *args);
t_arg				*upper_u_to_a(va_list ap, t_arg *args);

/*
** converter_x.c
*/
t_arg				*lower_x_to_a(va_list ap, t_arg *args);
t_arg				*upper_x_to_a(va_list ap, t_arg *args);

/*
** converter_wchar.c
*/
char				*convert_wchar(wchar_t c, t_arg *args);

/*
** error.c
*/
t_arg				*error_handler_with_ap(va_list ap, t_arg *args);
int					error_handler_without_ap(t_arg *args);

/*
** ft_printf.c
*/
int					ft_printf(const char *format, ...);

/*
** handler_args.c
*/
t_arg				*add_node(t_arg *args);

/*
** handler_conversion.c
*/
t_arg				*handle_conversion(va_list ap, t_arg *args, char **fmt);

/*
** handler_flags.c
*/
t_arg				*handle_flags(t_arg *args, char **fmt);

/*
** handler_min_width.c
*/
t_arg				*handle_min_width(va_list ap, t_arg *args, char **fmt);

/*
** handler_precision.c
*/
t_arg				*handle_precision(va_list ap, t_arg *args, char **fmt);

/*
** handler_size.c
*/
t_arg				*handle_size(t_arg *args, char **fmt);

/*
** manipulate_id.c
*/
t_arg				*id_width_flag_precision(t_arg *args);

/*
** manipulate_oux.c
*/
t_arg				*oux_width_flag_precision(t_arg *args);

/*
** manipulate_s.c
*/
t_arg				*s_width_flag_precision(t_arg *args);

/*
** manipulate_p.c
*/
t_arg				*p_width_flag(t_arg *args);

/*
** parser.c
*/
t_arg				*parse(va_list ap, t_arg *args, char *fmt);

#endif
