/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_cmd_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:44 by roguille          #+#    #+#             */
/*   Updated: 2025/09/25 16:37:52 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* A partir de la liste de tokens tok, crée une liste chaînée t_cmd
où chaque noeud contient:
-le tableau de commandes (pour execve)
-la liste de redirections associée à chaque commande */
t_cmd	*link_cmd_redir(t_token *tok, t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*curr_tok;
	t_token	*block_start;
	t_redir	*redir;
	int		heredoc_count;

	curr_tok = tok;
	cmd = NULL;
	heredoc_count = 0;
	while (curr_tok)
	{
		redir = NULL;
		block_start = curr_tok;
		if (!extract_redir(&curr_tok, &redir, shell, &heredoc_count))
			return (ft_free_redir(redir), NULL);
		if (!append_cmd(&cmd, block_start, redir))
			return (ft_free_full_cmd(cmd), NULL);
		if (curr_tok && curr_tok->type == PIPE)
			curr_tok = curr_tok->next;
	}
	return (cmd);
}
