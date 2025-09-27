/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:28 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 11:10:24 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Fonction de création de la liste de tokens qui sera utilisée pour le
parsing

1) Si des quotes ne sont pas fermées --> renvoie NULL
2) On met les tokens dans un tableau de char
3) On ajoute ensuite tous les tokens dans une liste chaînée
avec leur valeur, leur type, et si c'est une redirection (0 par
défaut, valeur updatée lors du parsing)
4) Si la syntaxe de la liste n'est pas bonne on free

Retourne la liste complétée en cas de succès
*/
t_token	*list_tokens(char *str, t_shell *shell)
{
	t_token	*list;
	char	**tokens;
	int		i;

	if (!has_closed_quotes(str))
		return (NULL);
	list = NULL;
	tokens = ft_tokenize(str);
	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		append_token(&list, tokens[i], get_t_type(tokens[i]));
		i++;
	}
	ft_free_tab(tokens);
	if (check_tokens(list, shell))
	{
		ft_free_tokens(list);
		return (NULL);
	}
	return (list);
}
