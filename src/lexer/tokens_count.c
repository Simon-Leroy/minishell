/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:35 by roguille          #+#    #+#             */
/*   Updated: 2025/09/25 16:35:14 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Si symbole d'input ou d'output on verifie si le symbole suivant
est identique pour determiner si append ou heredoc
On compte un mot supplementaire et fait avancer le curseur adequatement */
static void	handle_separator(char *s, size_t *i, int *words)
{
	if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] && s[*i] == s[*i + 1])
	{
		(*i)++;
		(*words)++;
	}
	else
		(*words)++;
}

// Compte le nombre de tokens qu'il y a dans la string pour pouvoir
// allouer en mémoire un tableau de strings
int	tokens_count(char *s)
{
	size_t	i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			validate_quote_closure(s, s[i], &i);
			if (check_char(s[i + 1]))
				words++;
		}
		else if (is_separator(s[i]))
			handle_separator(s, &i, &words);
		else if (!check_char(s[i]) && (check_char(s[i + 1])
				|| is_separator(s[i + 1])))
			words++;
		i++;
	}
	return (words);
}
