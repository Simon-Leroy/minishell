#include "minishell.h"

// A partir de la liste de tokens tok, crée une liste chaînée t_cmd
// où chaque noeud contient:
// -le tableau de commandes (pour execve)
// -la liste de redirections associée à chaque commande
t_cmd	*link_cmd_redir(t_token *tok)
{
	t_cmd	*cmd;
	t_token	*curr_tok;
	t_token	*block_start;
	t_redir	*redir;

	curr_tok = tok;
	cmd = NULL;
	while (curr_tok)
	{
		redir = NULL;
		block_start = curr_tok;
		if (!extract_redir(&curr_tok, &redir))
			return (ft_free_redir(redir), NULL);
		if (!append_cmd(&cmd, block_start, redir))
			return (ft_free_full_cmd(cmd), NULL);
		if (curr_tok && curr_tok->type == PIPE)
			curr_tok = curr_tok->next;
	}
	return (cmd);
}

void	expand_cmd_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	while (tmp->commands && tmp->commands[i])
	{
		if (ft_strchr(tmp->commands[i], '$'))
		{
			expanded = expand_str(tmp->commands[i], shell);
			free(tmp->commands[i]);
			tmp->commands[i] = expanded;
		}
		i++;
	}
}

void	expand_redirections(t_redir *redir, t_shell *shell)
{
	t_redir	*tmp_redir;
	char	*expanded;

	tmp_redir = redir;
	while (tmp_redir)
	{
		if (ft_strchr(tmp_redir->filename, '$'))
		{
			expanded = expand_str(tmp_redir->filename, shell);
			free(tmp_redir->filename);
			tmp_redir->filename = expanded;
		}
		tmp_redir = tmp_redir->next;
	}
}

void	expand_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	expand_cmd_args(cmd, shell);
	expand_redirections(cmd->redir, shell);
}

/* int main(void)
{
	char *test = "bonjour $9USER < infile | cat >> $HOME/text.txt | grep $HOME.non | test $0HOME$ $=USER$";

	t_token *tokens;
	t_cmd	*cmd;
	t_cmd	*tmp;

	tokens = list_tokens(test);
	cmd = link_cmd_redir(tokens);
	expand_cmd(cmd);
 	tmp = cmd;
	while (tmp)
	{
		printf("Command:\n");
		for (int i = 0; tmp->commands[i]; i++)
			printf("  - %s\n", tmp->commands[i]);
		t_redir *r = tmp->redir;
		while (r)
		{
			printf("  Redirection: type %d → %s\n", r->type, r->filename);
			r = r->next;
		}
		tmp = tmp->next;
	}
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
} */
