#include "minishell.h"

// Renvoie 1 si les quotes sont bien fermées, 0 sinon
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
