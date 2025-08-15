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
