#include "minishell.h"

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

void	remove_quotes_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;
	char	*no_quotes;
	int		i;

	tmp_cmd = cmd;
	i = 0;
	while (tmp_cmd && tmp_cmd->commands[i])
	{
		no_quotes = remove_quotes(tmp_cmd->commands[i]);
		free(tmp_cmd->commands[i]);
		tmp_cmd->commands[i] = no_quotes;
		i++;
		tmp_redir = tmp_cmd->redir;
		while (tmp_redir)
		{
			no_quotes = remove_quotes(tmp_redir->filename);
			free(tmp_redir->filename);
			tmp_redir->filename = no_quotes;
			tmp_redir = tmp_redir->next;
		}
	}
}

void	remove_empty_args(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->commands[i])
	{
		if (cmd->commands[i][0] != '\0')
			cmd->commands[j++] = cmd->commands[i];
		else
			free(cmd->commands[i]);
		i++;
	}
	cmd->commands[j] = NULL;
}

void	expand_remove_quotes_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	expand_cmd_args(cmd, shell);
	expand_redirections(cmd->redir, shell);
	remove_quotes_cmd(cmd);
	remove_empty_args(cmd);
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
