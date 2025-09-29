/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:49 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 11:14:01 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
-Si le token suivant est un mot la redirection est invalide
-Si le type est un heredoc on appelle la fonction de gestion
des heredoc
-Sinon appelle la fonction d'ajout des redirections à la liste
chaînée des redirections
*/
int	process_redir_token(t_token *tok, t_redir **redir,
	int *heredoc_count, t_shell *shell)
{
	if (!tok->next || tok->next->type != WORD)
	{
		perror("Syntax error");
		return (0);
	}
	if (tok->type == HEREDOC)
	{
		if (!handle_heredoc(tok, *heredoc_count, shell))
			return (0);
		(*heredoc_count)++;
	}
	if (!append_redir(redir, tok))
		return (0);
	return (1);
}

/*
Parcourt les tokens avant un pipe et extrait les redirections
Si ce n'est ni un pipe ni un WORD, c'est forcément une redirection
*/
int	extract_redir(t_token **tok, t_redir **redir,
	t_shell *shell, int *heredoc_count)
{
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type != WORD)
		{
			if (!process_redir_token(*tok, redir, heredoc_count, shell))
				return (0);
			*tok = (*tok)->next->next;
		}
		else
			*tok = (*tok)->next;
	}
	return (1);
}
