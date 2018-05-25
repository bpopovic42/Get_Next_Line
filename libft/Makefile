NAME	=	libft.a

CC		=	gcc

SRC		=	ft_islower.c \
	ft_isupper.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putnbr.c \
	ft_strlen.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strrchr.c \
	ft_strchr.c \
	ft_strchrin.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_itoa_base.c \
	ft_putnbr_base.c \
	ft_putstr_npr.c \
	ft_print_memory.c \
	ft_atoi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_itoa.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_issign.c \
	ft_char_count.c \
	ft_lstpush.c \
	ft_strappend.c \
	ft_strnappend.c \
	ft_del.c \
	ft_hashnew.c \
	ft_hashpopkey.c \
	ft_hashpush.c \
	ft_hashdel.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

HEADERS	=	libft.h

all		:	$(NAME)
			@echo > /dev/null

$(NAME)	:	$(OBJ)
			@ar rc $(NAME) $(OBJ)
			@ranlib $(NAME)
			@echo "[96mLibft [92mCompiled[0m"

%.o		:	%.c $(HEADERS)
			@$(CC) $(CFLAGS) -I $(HEADERS) -c -o $@ $<

clean	:
			@echo "Cleaning the [96mLibft[0m files..."
			@rm -f $(OBJ)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all

.PHONY	: all, clean, fclean, re
