NAME		=	libft.a

CC			=	gcc

SDIR		=	./srcs/

ODIR		=	./objs/

IDIR		=	./includes/

SRCS		=	ft_islower.c \
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
	ft_strchri.c \
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
	ft_hashnew.c \
	ft_hashpop.c \
	ft_hashget.c \
	ft_hashpush.c \
	ft_hashdel.c \
	ft_hashadd.c \
	ft_memapp.c \
	ft_memcat.c \
	ft_memchri.c \
	ft_memdup.c \
	ft_putstrn.c

OBJS		=	$(SRCS:.c=.o)

HEADERS		=	libft.h

HEADER		=	$(addprefix $(IDIR), $(HEADERS))

SRC			=	$(addprefix $(SDIR), $(SRCS))

OBJ			=	$(addprefix $(ODIR), $(OBJS))

INC			=	$(addprefix -I,$(IDIR))

CFLAGS		=	-Wall -Wextra -Werror

all			:	$(NAME)
			@echo > /dev/null

$(NAME)		:	$(OBJ)
			@ar rc $(NAME) $(OBJ)
			@ranlib $(NAME)
			@echo "[96mLibft [92mCompiled[0m"

$(OBJ)		:	| $(ODIR)

$(ODIR)		:
			@mkdir objs

$(ODIR)%.o	:	$(SDIR)%.c $(HEADER)
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean		:
			@echo "Cleaning the [96mLibft[0m files..."
			@rm -f $(OBJ)
			@rm -rf $(ODIR)

fclean		:	clean
			@rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re
