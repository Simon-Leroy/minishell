/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:46 by roguille          #+#    #+#             */
/*   Updated: 2025/09/25 16:44:45 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Renvoie 1 si les quotes sont bien fermées, 0 sinon.
On fait avancer la chaine de caractere jusqu'a la fin des quotes
ou la fin de la chaine
Va permettre de conserver dans un seul token les caracteres sous quote*/
int	validate_quote_closure(char *str, char delim, size_t *index)
{
	if (str[*index] == delim)
	{
		(*index)++;
		while (str[*index] && str[*index] != delim)
			(*index)++;
		if (str[*index] == '\0')
			return (0);
	}
	return (1);
}

// S'assure que toutes les quotes de la string passée sont bien fermées (1)
// renvoie 0 sinon
int	has_closed_quotes(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'')
		{
			if (!validate_quote_closure(str, '\'', &index))
				return (0);
		}
		else if (str[index] == '"')
		{
			if (!validate_quote_closure(str, '\"', &index))
				return (0);
		}
		index++;
	}
	return (1);
}
