/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:30 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 10:38:04 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

/*
ft_split mais pour les tokens

1) Skip les whitespaces
2) On mesure la len du token
3) On copie le token dans le tableau
4) On avance le curseur dans s pour skip tout le token
5) On incrémente i pour passer à la str suivante du tableau
*/
char	**ft_tokenize(char *s)
{
	char	**tab;
	size_t	i;
	size_t	tokens;
	size_t	token_len;

	tokens = tokens_count(s);
	tab = malloc(sizeof(char *) * (tokens + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < tokens)
	{
		if (!s || !*s)
			break ;
		while (check_char(*s))
			s++;
		token_len = ft_token_len(s);
		tab[i] = token_copy(s);
		if (!tab[i])
			return (free_tab(tab, i), NULL);
		s += token_len;
		i++;
	}
	tab[tokens] = 0;
	return (tab);
}

/* int main()
{
	char *str = "bonjour | \"tous>>>bon\"";
	char **tab;

	tab = ft_tokenize(str);
	int	i = 0;
	if (!tab || !*tab)
		return (0);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
} */
