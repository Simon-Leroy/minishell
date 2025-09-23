/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:32 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:34 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Renvoie un pointeur vers le dernier noeud de la liste chaînée de tokens
t_token	*ft_lst_last_token(t_token *list)
{
	t_token	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// Ajoute un nouveau token à la liste chaînée et crée le premier noeud
// si la liste est vide
int	append_token(t_token **list, char *value, t_token_type type)
{
	t_token	*new_node;
	t_token	*last;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (0);
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->is_redir = 0;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		last = ft_lst_last_token(*list);
		last->next = new_node;
	}
	return (1);
}
