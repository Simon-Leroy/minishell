NAME = minishell

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXPAND_DIR = $(SRC_DIR)/expander
EXEC_DIR = $(SRC_DIR)/executor
UTILS_DIR = $(SRC_DIR)/utils
BUILTINS_DIR = $(SRC_DIR)/built_ins


SRCFILES = \
	$(EXEC_DIR)/count_cmd.c \
	$(EXEC_DIR)/exec_cmd.c \
	$(EXEC_DIR)/heredoc.c \
	$(EXEC_DIR)/multiple_cmd.c \
	$(EXEC_DIR)/path_handler.c \
	$(EXEC_DIR)/pipe_utils.c \
	$(EXEC_DIR)/redirections.c \
	$(EXEC_DIR)/run_commands.c \
	$(EXEC_DIR)/single_cmd.c \
	$(EXPAND_DIR)/dollar_classify.c \
	$(EXPAND_DIR)/expand.c \
	$(EXPAND_DIR)/expander_quotes.c \
	$(EXPAND_DIR)/var_copy.c \
	$(EXPAND_DIR)/var_len.c \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/token_list.c \
	$(LEXER_DIR)/token_types.c \
	$(LEXER_DIR)/tokenizer_utils.c \
	$(LEXER_DIR)/tokenizer.c \
	$(PARSER_DIR)/cmd_block_create.c \
	$(PARSER_DIR)/cmd_expand_quotes.c \
	$(PARSER_DIR)/cmd_list_utils.c \
	$(PARSER_DIR)/link_cmd_redir.c \
	$(PARSER_DIR)/quote_validation.c \
	$(PARSER_DIR)/redir_list_utils.c \
	$(PARSER_DIR)/redir_process.c \
	$(UTILS_DIR)/error.c \
	$(UTILS_DIR)/free.c \
	$(UTILS_DIR)/utils.c \
	$(BUILTINS_DIR)/exec_builtin.c \
	$(BUILTINS_DIR)/exit.c \
	main.c

OBJFILES = $(SRCFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

LIBFTPATH = libft

LIBFTLIB = $(LIBFTPATH)/libft.a

CC = cc

RM = rm -f

all: subdirectories $(NAME)

$(NAME): $(OBJFILES)
			$(CC) -o $(NAME) $(OBJFILES) $(CFLAGS) $(LIBFTLIB) -lreadline

subdirectories :
			make -C $(LIBFTPATH)

norm :
			norminette libft minishell.h $(SRCFILES)

clean:
			$(RM) $(OBJFILES)
			make -C $(LIBFTPATH) clean

fclean: clean
			$(RM) $(NAME)
			make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: clean fclean all re norm subdirectories
