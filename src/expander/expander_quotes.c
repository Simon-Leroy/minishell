/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:20 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 12:28:12 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Met à jour l'état des guillemets et détermine si on est à l'intérieur
ou à l'extérieur de quotes.

-Si le caractère est une single quote et qu'on n'est pas dans des doubles
quotes, on inverse l'état de s_quote et on skip la quote avec i++

-Si le caractère est une double quote, pareil mais inversé
*/
static void	handle_quotes(char *str, int *d_quote, int *s_quote, int *i)
{
	if (str[*i] == '\'' && !*d_quote)
	{
		*s_quote = !*s_quote;
		(*i)++;
	}
	else if (str[*i] == '"' && !*s_quote)
	{
		*d_quote = !*d_quote;
		(*i)++;
	}
}

/* Calcule la longueur de la chaîne après la suppression des quotes inutiles
"Hello 'World'" --> Hello 'World' --> 13 */
size_t	len_without_quotes(char *str)
{
	size_t	len;
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	len = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		handle_quotes(str, &in_double, &in_single, &i);
		if (str[i] && !((str[i] == '\'' && !in_double)
				|| (str[i] == '"' && !in_single)))
		{
			len++;
			i++;
		}
	}
	return (len);
}

/*
Même fonctionnement que la fonction précédente mais en copiant les
caractères dans une nouvelle chaîne plutôt que de compter la longueur
*/
char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		k;
	int		in_single;
	int		in_double;

	new_str = malloc(len_without_quotes(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		handle_quotes(str, &in_double, &in_single, &i);
		if (str[i] && !((str[i] == '\'' && !in_double)
				|| (str[i] == '"' && !in_single)))
			new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	return (new_str);
}
