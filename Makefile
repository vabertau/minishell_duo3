NAME = minishell

CC = cc $(FLAGS) -g

#FLAGS = -Wall -Werror -Wextra

FILENAMES = main.c parsing/get_input.c parsing/lexer.c parsing/nb_tokens.c parsing/spaces_bet_tokens.c \
free/exit_free.c parsing/skip_q.c parsing/malloc_tokens.c parsing/init_data.c parsing/fill_tokens.c parsing/ft_quotesplit.c \
parsing/copy_bet_q.c parsing/fill_types.c checks/check_unclosedq.c parsing/parsing_error.c checks/checks.c checks/check_schar_error.c \
checks/check_pipe_ext.c parsing/pnb_cmd.c parsing/parser.c parsing/pmalloc_exec.c parsing/pfill_full_cmd.c parsing/pfill_split_cmd.c parsing/pfill_redir.c \
parsing/pinit_exec.c executor/executor.c expands/expands.c checks_tokens/check_redirfile.c sig.c \
executor/finish_him.c executor/redir.c executor/safe_op.c executor/utils.c \
builtins/ft_echo.c builtins/dir.c builtins/env.c checks/check_fasa.c expands/is_to_expand.c expands/replace_var.c \
free/exit_free2.c parsing/spaces_bet_tokens2.c parsing/pfill_redir2.c parsing/ft_quotesplit2.c

SRCS = $(addprefix srcs/, $(FILENAMES))

OBJS = $(SRCS:.c=.o)

FT_PRINTF = libftprintf/libftprintf.a

FT_PRINTF_PATH = libftprintf

$(NAME): $(FT_PRINTF) $(OBJS)
	$(CC) $(OBJS) $(FT_PRINTF) -lreadline -o $(NAME)

$(FT_PRINTF):
	make -C $(FT_PRINTF_PATH) all

clean:
	make -C $(FT_PRINTF_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(FT_PRINTF_PATH) fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)
