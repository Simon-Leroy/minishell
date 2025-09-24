/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_block_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:38 by roguille          #+#    #+#             */
/*   Updated: 2025/09/24 12:31:36 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Alloue la mémoire nécessaire pour créer la liste chaînée de commandes
t_cmd	*allocate_cmd_block(t_token *tok)
{
	t_cmd	*cmd_block;
	size_t	count_cmd;
	size_t	i;

	cmd_block = malloc(sizeof(t_cmd));
	if (!cmd_block)
		return (NULL);
	count_cmd = nb_cmd_by_block(tok);
	cmd_block->commands = malloc(sizeof(char *) * (count_cmd + 1));
	if (!cmd_block->commands)
	{
		free(cmd_block);
		return (NULL);
	}
	while (i <= count_cmd)
		cmd_block->commands[i++] = NULL;
	cmd_block->redir = NULL;
	cmd_block->next = NULL;
	return (cmd_block);
}

// Met les données dans le noeud de commande
int	populate_cmd_block(t_cmd *cmd_block, t_token *tok, t_redir *redir)
{
	t_token	*tmp;
	int		i;

	tmp = tok;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->is_redir == 0)
		{
			cmd_block->commands[i] = ft_strdup(tmp->value);
			if (!cmd_block->commands[i])
			{
				while (--i >= 0)
				{
					free(cmd_block->commands[i]);
					cmd_block->commands[i] = NULL;
				}
				free(cmd_block->commands);
				cmd_block->commands = NULL;
				return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	cmd_block->commands[i] = 0;
	cmd_block->redir = redir;
	cmd_block->next = NULL;
	return (1);
}

// Ajoute une nouvelle commande à la liste chaînée des commandes
int	append_cmd(t_cmd **head, t_token *tok, t_redir *redir)
{
	t_cmd	*new_cmd;
	t_cmd	*last;

	new_cmd = allocate_cmd_block(tok);
	if (!new_cmd)
		return (0);
	if (!populate_cmd_block(new_cmd, tok, redir) || !new_cmd->commands[0])
	{
		ft_free_full_cmd(new_cmd);
		return (0);
	}
	if (!*head)
		*head = new_cmd;
	else
	{
		last = ft_lst_last_cmd(*head);
		last->next = new_cmd;
	}
	return (1);
}
