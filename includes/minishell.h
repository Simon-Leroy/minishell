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
# include "../libft/libft.h"
# include <linux/limits.h>

typedef enum e_token_type
{
	PIPE,
	WORD,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
} t_token_type;

typedef enum e_env_var_type
{
	ENV_VAR,
	LITERAL,
	INVALID,
	EXIT_STATUS
} t_env_var_type;

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
	t_token_type	type;
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

typedef	struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_shell
{
	int				last_exit_code;
	t_env			*env;
} t_shell;


// LEXER PART

t_token	*list_tokens(char *str);
int	append_token(t_token **list, char *value, t_token_type type);
t_token_type get_t_type(char *str);
char	*token_copy(char *s);

int	tokens_count(char *s);
size_t	ft_token_len(char *str);
int	check_char(char c);
char	**ft_tokenize(char *s);

// PARSER PART

int	append_cmd(t_cmd **head, t_token *tok, t_redir *redir);
void	expand_remove_quotes_cmd(t_cmd *cmd, t_shell *shell);
t_cmd	*ft_lst_last_cmd(t_cmd *list);
size_t	nb_cmd_by_block(t_token	*tokens);
t_cmd	*link_cmd_redir(t_token *tok);

int	has_closed_quotes(char *str);
int	validate_quote_closure(char *str, char delim, size_t *index);
int	append_redir(t_redir **head, t_token *tok);
int	extract_redir(t_token **tok, t_redir **redir);

// EXPANDER PART

char	*extract_var_name(char *str);
char	*expand_str(char *str, t_shell *shell);
char	*remove_quotes(char *str);
t_env_var_type classify_dollar(char c);
void	process_env_var_copy(char *str, size_t *i, char *exp, size_t *k, t_shell *shell);
size_t	expanded_len(char *str, t_shell *shell);

// EXECUTOR PART

size_t	get_nbr_commands(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd, t_shell *shell);
int	handle_heredoc(t_token *tok, int heredoc_count);

void	single_command(t_cmd *cmd, t_shell *shell);
void	multiple_commands(t_cmd *cmd, pid_t *pids, t_shell *shell);
char	*get_path(t_cmd *cmd);

void	check_close(int fd);
void	close_pipe(int *fd);

int	apply_redirections(t_redir *redir, t_shell *shell);
void	run_commands(t_cmd *cmd, t_shell *shell);

// BUILT-INS

int	exec_builtin(t_cmd *cmd, t_shell *shell);
int is_parent_builtin(char *name);

void	set_env(t_env **env, char *key, char *value);
t_env	*init_env(char **envp);
char	**build_envp(t_env *env);

int	ft_exit(char **args, int last_status);
int	ft_pwd(void);
int	ft_echo(char **args);
int	ft_cd(char **args);
int	ft_env(t_shell *shell);
int	ft_export(char **args, t_env **env);


// UTILS

void	set_exit_code_errno(t_shell *shell);
void	print_error(char *command, int exit_code);

void	ft_free_tab(char **tab);
void	ft_free_tokens(t_token *list);
void	ft_free_redir(t_redir *redir);
void	ft_free_full_cmd(t_cmd *cmd);
void	ft_free_env(t_env *env);

int	int_len(int nb);
int	ft_strcmp(char *s1, char *s2);











/*
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

// expander.c
char	*expand_str(char *str, t_shell *shell);

// manage_redirections.c
int	redirect(t_cmd *cmd);

int apply_redirections(t_redir *redir, t_shell *shell);

char	*path_handler(char *cmd);
void	exec_cmd(t_cmd *cmd, char **envp, t_shell *shell);

char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strcpy(char *dest, char *src);

int	first_command(t_cmd *cmd, char **envp, pid_t *pid_out, t_shell *shell);
int	middle_pipes(t_cmd *cmd, char **envp, int *fd, pid_t *pid_out, t_shell *shell);
int	last_command(t_cmd *cmd, char **envp, int *fd, pid_t *pid_out, t_shell *shell);

void	expand_remove_quotes_cmd(t_cmd *cmd, t_shell *shell);

void	run_commands(t_cmd *cmd, char **envp, t_shell *shell);

void	set_exit_code_errno(t_shell *shell);

// utils.c
int	int_len(int nb);

//heredoc.c
int		heredoc_fd(char *eof, int file_number);
char	*generate_tmp_filename(int	i);

int	ft_strcmp(char *s1, char *s2);

int	handle_heredoc(t_token *tok, int heredoc_count);

char	*remove_quotes(char *str); */


#endif
