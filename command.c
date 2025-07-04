#include "minishell.h"

// Renvoie un pointeur vers le dernier noeud de la liste chaînée de commandes
t_cmd	*ft_lst_last_cmd(t_cmd *list)
{
	t_cmd	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// 1 bloc = commandes + redirection délimitées par un pipe
// Compte le nombre de commandes dans un bloc

// /!\ /!\ Pour fonctionner il faut d'abord que le travail sur
//         les redirections ait été fait (voir redirection.c)

size_t	nb_cmd_by_block(t_token	*tokens)
{
	t_token	*current;
	int		count;

	count = 0;
	current = tokens;
	while (current != NULL && current->type != PIPE)
	{
		if (current->is_redir == 0)
			count++;
		current = current->next;
	}
	return (count);
}

// Alloue la mémoire nécessaire pour créer la liste chaînée de commandes
t_cmd	*allocate_cmd_block(t_token *tok)
{
	t_cmd	*cmd_block;
	size_t	count_cmd;

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
					free(cmd_block->commands[i]);
				free(cmd_block->commands);
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
	if (!populate_cmd_block(new_cmd, tok, redir))
	{
		free(new_cmd);
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
