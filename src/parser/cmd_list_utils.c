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
