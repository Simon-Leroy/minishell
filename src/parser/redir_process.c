#include "minishell.h"

// Traite un token de redirection simple (INPUT, OUTPUT, APPEND, HEREDOC)
// Appelle handle_heredoc si c'est un heredoc

int	process_redir_token(t_token *tok, t_redir **redir, int *heredoc_count)
{
	if (!tok->next || tok->next->type != WORD)
	{
		perror("Syntax error");
		return (0);
	}
	if (tok->type == HEREDOC)
	{
		if (!handle_heredoc(tok, *heredoc_count))
			return (0);
		(*heredoc_count)++;
	}
	if (!append_redir(redir, tok))
		return (0);
	return (1);
}

// Parcourt les tokens avant un pipe et extrait les redirections
int	extract_redir(t_token **tok, t_redir **redir)
{
	int	heredoc_count = 0;

	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type != WORD)
		{
			if (!process_redir_token(*tok, redir, &heredoc_count))
				return (0);
			*tok = (*tok)->next->next;
		}
		else
			*tok = (*tok)->next;
	}
	return (1);
}
