/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:52:40 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:52:41 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>

# define _XOPEN_SOURCE 700

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	PIPE,
	WORD,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_env_var_type
{
	ENV_VAR,
	LITERAL,
	INVALID,
	EXIT_STATUS
}	t_env_var_type;

// Liste chaînée avec :
// -valeur : string qui peut être une commande un < un >> etc
// -is_redir : booléen 1 si le token est une redirection
// (filename ou symbole) 0 sinon
// -type : basé sur le enum juste au dessus
// -next : pointeur vers le token suivant dans la liste
typedef struct s_token
{
	char			*value;
	int				is_redir;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// -type : type de redirection basé sur le enum
// -filename : filename qui suit toujours une redirection
typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

// structure de commande pour la partie d'exécution du minishell
// -**commands : tableau de commandes à passer en argument de execve
// -redir : pointeur vers la liste chaînée des redirections
// à gérer avant de faire le execve
typedef struct s_cmd
{
	char			**commands;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int				last_exit_code;
	t_env			*env;
}	t_shell;

// LEXER PART

t_token			*list_tokens(char *str, t_shell *shell);
int				append_token(t_token **list, char *value, t_token_type type);
t_token_type	get_t_type(char *str);
char			*token_copy(char *s);
int				is_separator(char c);
int				tokens_count(char *s);
size_t			ft_token_len(char *str);
int				check_char(char c);
char			**ft_tokenize(char *s);
int				check_tokens(t_token *tokens, t_shell *shell);

// PARSER PART

int				append_cmd(t_cmd **head, t_token *tok, t_redir *redir);
void			expand_remove_quotes_cmd(t_cmd *cmd, t_shell *shell);
t_cmd			*ft_lst_last_cmd(t_cmd *list);
size_t			nb_cmd_by_block(t_token	*tokens);
t_cmd			*link_cmd_redir(t_token *tok, t_shell *shell);

int				has_closed_quotes(char *str);
int				validate_quote_closure(char *str, char delim, size_t *index);
int				append_redir(t_redir **head, t_token *tok);
int				extract_redir(t_token **tok, t_redir **redir,
					t_shell *shell, int *heredoc_count);

void			expand_cmd_args(t_cmd *cmd, t_shell *shell);
void			expand_redirections(t_redir *redir, t_shell *shell);
void			remove_quotes_args(t_cmd *cmd);
void			remove_quotes_redir(t_cmd *cmd);
void			remove_empty_args(t_cmd *cmd);

// EXPANDER PART

char			*extract_var_name(char *str);
char			*expand_str(char *str, t_shell *shell);
char			*remove_quotes(char *str);
t_env_var_type	classify_dollar(char c);
void			process_env_var_copy(char **str, char **exp, t_shell *shell);
size_t			expanded_len(char *str, t_shell *shell);
char			*get_env_value(t_env *env, char *key);

// EXECUTOR PART

size_t			get_nbr_commands(t_cmd *cmd);
void			exec_cmd(t_cmd *cmd, t_shell *shell);
void			check_path(char *cmd, char *path, t_shell *shell);

char			*generate_tmp_filename(int i);
int				handle_heredoc(t_token *tok, int heredoc_count, t_shell *shell);
void			write_heredoc_input(char *str, int fd);
void			write_heredoc_eof_error(char *eof);

void			single_command(t_cmd *cmd, t_shell *shell);
void			multiple_commands(t_cmd *cmd, pid_t *pids, t_shell *shell);
char			*get_path(t_cmd *cmd, t_env *env);

void			check_close(int fd);
void			close_pipe(int *fd);

int				first_command(t_cmd *cmd, pid_t *pid_out, t_shell *shell);
int				middle_pipes(t_cmd *cmd, int *fd, pid_t *pid_out,
					t_shell *shell);
int				last_command(t_cmd *cmd, int *fd, pid_t *pid_out,
					t_shell *shell);

int				apply_redirections(t_redir *redir, t_shell *shell);
void			run_commands(t_cmd *cmd, t_shell *shell);

// BUILT-INS

int				exec_builtin(t_cmd *cmd, t_shell *shell);
int				is_parent_builtin(char *name);

void			set_env(t_env **env, char *key, char *value);
t_env			*init_env(char **envp);
int				env_count(t_env *env);
void			print_env(t_env *env);

char			**build_envp(t_env *env);
int				is_valid_identifier(char *str);

int				ft_exit(char **args, int last_status);
int				ft_pwd(void);
int				ft_echo(char **args);
int				ft_cd(char **args, t_env *env);
int				ft_env(t_shell *shell);
int				ft_export(char **args, t_env **env);
int				ft_unset(char **args, t_env **env);

// UTILS

void			exit_errno(t_shell *shell);
void			print_error(char *command, int exit_code);
void			write_error(char *cmd, char *msg);

void			ft_free_tab(char **tab);
void			ft_free_tokens(t_token *list);
void			ft_free_redir(t_redir *redir);
void			ft_free_full_cmd(t_cmd *cmd);
void			ft_free_env(t_env *env);

void			sigint_handler(int signum);
void			sigquit_handler(int signum);
void			restore_signal(void);
void			ignore_signal(void);
void			setup_signal(void);

int				int_len(int nb);
int				ft_strcmp(char *s1, char *s2);

#endif
