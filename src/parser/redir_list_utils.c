#include "minishell.h"

// Retourne un pointeur sur le dernier noeud de la liste t_redir
// renvoie NULL si la liste est vide
t_redir	*ft_lst_last_redir(t_redir *list)
{
	t_redir	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	append_redir(t_redir **head, t_token *tok)
{
	t_redir	*new_node;
	t_redir	*last;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (0);
	if (!tok->next || tok->next->type != WORD)
		return (free(new_node), 0);
	new_node->type = tok->type;
	new_node->filename = ft_strdup(tok->next->value);
	if (!new_node->filename)
		return (free(new_node), 0);
	new_node->next = NULL;
	tok->is_redir = 1;
	tok->next->is_redir = 1;
	if (!*head)
		*head = new_node;
	else
	{
		last = ft_lst_last_redir(*head);
		last->next = new_node;
	}
	return (1);
}
