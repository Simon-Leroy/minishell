NAME = minishell

SRCFILES =	check_quotes.c \
			command.c \
			free.c \
			ft_tokenize.c \
			lexing.c \
			redirection.c \
			path_handler.c \
			manage_redirections.c \
			manage_pipes.c \
			exec_command.c \
			expander.c \
			parser.c \
			utils.c \
			error.c \
			heredoc.c \
			main.c

OBJFILES = $(SRCFILES:.c=.o)

CFLAGS = -lreadline -Wall -Wextra -Werror -g

LIBFTPATH = libft

LIBFTLIB = $(LIBFTPATH)/libft.a

CC = cc

RM = rm -f

all: subdirectories $(NAME)

$(NAME): $(OBJFILES)
			$(CC) -o $(NAME) $(OBJFILES) $(CFLAGS) $(LIBFTLIB)

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
