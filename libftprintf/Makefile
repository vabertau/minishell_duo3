NAME = libftprintf.a

LIBFT = $(LIBFT_PATH)/libft.a

CC=cc

CFLAGS=-Wall -Wextra -Werror

RM = rm -f

SRC = ft_printf.c ft_putptr.c utils.c

OBJ = $(SRC:.c=.o)

LIBFT_PATH = libft/

$(NAME): $(LIBFT) $(OBJ)
		cp $(LIBFT_PATH)/libft.a $(NAME)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

$(LIBFT):
		make -C $(LIBFT_PATH) all

%.o: %.c
		$(CC) -I. -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
		make -C $(LIBFT_PATH) clean
		$(RM) $(OBJ)

fclean: clean
		make -C $(LIBFT_PATH) fclean
		$(RM) $(NAME)

re: fclean all
