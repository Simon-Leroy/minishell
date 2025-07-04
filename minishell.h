#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"

typedef enum e_token_type
{
	PIPE,
	WORD,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
} t_token_type;

// Liste chaînée avec :
// -valeur : string qui peut être une commande un < un >> etc
// -is_redir : booléen 1 si le token est une redirection (filename ou symbole) 0 sinon
// -type : basé sur le enum juste au dessus
// -next : pointeur vers le token suivant dans la liste
typedef struct s_token
{
	char			*value;
	int				is_redir;
	t_token_type	type;
	struct s_token	*next;
} t_token;

// -type : type de redirection basé sur le enum
// -filename : filename qui suit toujours une redirection
typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
} t_redir;

// structure de commande pour la partie d'exécution du minishell
// -**commands : tableau de commandes à passer en argument de execve
// -redir : pointeur vers la liste chaînée des redirections à gérer avant de faire le execve
typedef struct s_cmd
{
	char			**commands;
	t_redir			*redir;
	struct s_cmd	*next;
} t_cmd;

// PARTIE PARSING

// ft_tokenize.c
char	**ft_tokenize(char *s);
int		check_char(char c);
int		tokens_count(char *s);

// lexing.c
t_token	*list_tokens(char *str);
//void	print_type(int type);

// check_quotes.c
int	validate_quote_closure(char *str, char c, size_t *index);
int	has_closed_quotes(char *str);

// free.c
void	ft_free_tab(char **tab);
void	ft_free_redir(t_redir *redir);
void 	ft_free_tokens(t_token *list);
void	ft_free_full_cmd(t_cmd *cmd);

// parser.c
t_cmd	*link_cmd_redir(t_token *tok);

// redirection.c
int	append_redir(t_redir **head, t_token *tok);
int	extract_redir(t_token **tok, t_redir **redir);

// command.c
int	append_cmd(t_cmd **head, t_token *tok, t_redir *redir);



char	*path_handler(char *cmd);
void	exec_cmd(t_cmd *cmd, char **envp);





#endif
