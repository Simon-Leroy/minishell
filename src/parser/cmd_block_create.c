/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_block_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:38 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 11:12:30 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Alloue la mémoire nécessaire pour créer la liste chaînée de commandes */
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
	i = 0;
	while (i <= count_cmd)
		cmd_block->commands[i++] = NULL;
	cmd_block->redir = NULL;
	cmd_block->next = NULL;
	return (cmd_block);
}

/*
Fonction helper pour réduire la taille de la commande populate

Copie les args des commandes dans la structure t_cmd à partir
des tokens
 */
static int	copy_command(t_cmd *cmd_block, t_token *tok, int *i)
{
	cmd_block->commands[*i] = ft_strdup(tok->value);
	if (!cmd_block->commands[*i])
	{
		while (--(*i) >= 0)
		{
			free(cmd_block->commands[*i]);
			cmd_block->commands[*i] = NULL;
		}
		free(cmd_block->commands);
		cmd_block->commands = NULL;
		return (0);
	}
	(*i)++;
	return (1);
}

/*
Met toutes les données provenant des tokens dans la structure t_cmd

Si is_redir == 0 -> c'est un argument de commande donc on utilise
copy_command. Le dernier élément du tableau est un NULL.
On associe à cette structure les redirections qui ont été mises dans une autre
structure t_redir au préalable
*/
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
			if (!copy_command(cmd_block, tmp, &i))
				return (0);
		}
		tmp = tmp->next;
	}
	cmd_block->commands[i] = 0;
	cmd_block->redir = redir;
	cmd_block->next = NULL;
	return (1);
}

/*
Ajoute un bloc de commandes à la suite des autres dans la liste chaînée.
Si la liste est vide, le noeud créé devient la tête de la liste
*/
int	append_cmd(t_cmd **head, t_token *tok, t_redir *redir)
{
	t_cmd	*new_cmd;
	t_cmd	*last;

	new_cmd = allocate_cmd_block(tok);
	if (!new_cmd)
		return (0);
	if (!populate_cmd_block(new_cmd, tok, redir))
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
