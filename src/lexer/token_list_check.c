/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:34 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 11:01:19 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checke la cohérence de la liste de tokens :

- Si deux symboles pipe à la suite : erreur
- Si une redirection n'est pas suivie d'un mot/filename : erreur

Renvoie 0 en cas de succès
*/
static int	check_syntax(t_token *tokens, t_shell *shell)
{
	if (tokens->type == PIPE)
	{
		if (!tokens->next || tokens->next->type == PIPE)
		{
			write(2, "minishell: syntax error\n", 24);
			shell->last_exit_code = 2;
			return (1);
		}
	}
	if (tokens->type == INPUT || tokens->type == OUTPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		if (!tokens->next || tokens->next->type != WORD)
		{
			write(2, "minishell: syntax error\n", 24);
			shell->last_exit_code = 2;
			return (1);
		}
	}
	return (0);
}

/*
Checke toute la liste :

- Si la liste commence par un pipe : erreur
- On checke ensuite chaque token avec la fonction précédente

Renvoie 0 en cas de succès
*/
int	check_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*curr;

	if (!tokens)
		return (0);
	curr = tokens;
	if (curr->type == PIPE)
	{
		write(2, "minishell: syntax error\n", 24);
		shell->last_exit_code = 2;
		return (1);
	}
	while (curr)
	{
		if (check_syntax(curr, shell))
			return (1);
		curr = curr->next;
	}
	return (0);
}
