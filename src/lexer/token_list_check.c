/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:34 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:35 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
