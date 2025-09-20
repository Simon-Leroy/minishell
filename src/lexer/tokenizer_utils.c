#include "minishell.h"

// Détermine si le caractère est un white space ou une fin de chaîne
int	check_char(char c)
{
	if ((c >= 9 && c <= 12) || c == ' ' || c == '\0')
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

// Incrémente i et len jusqu'à ce que le délimiteur soit atteint
void	increment_len(char *str, size_t *i, size_t *len, char delim)
{
	(*i)++;
	(*len)++;
	while (str[*i] && str[*i] != delim)
	{
		(*i)++;
		(*len)++;
	}
	if (str[*i] == delim)
	{
		(*i)++;
		(*len)++;
	}
}

// Calcule la longueur du token pour allouer les caractères de chaque string
// du tableau
size_t	ft_token_len(char *s)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (is_separator(s[0]))
	{
		if ((s[0] == '>' || s[0] == '<') && s[1] && s[0] == s[1])
			return (len + 2);
		else
			return (len + 1);
	}
	while (s[i])
	{
		if (check_char(s[i]) || is_separator(s[i]))
			break ;
		if (s[i] == '\'' || s[i] == '"')
			increment_len(s, &i, &len, s[i]);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

// Copie un token
char	*token_copy(char *s)
{
	char		*token;
	size_t		token_len;
	size_t		i;

	token_len = ft_token_len(s);
	token = malloc(sizeof(char) * (token_len + 1));
	if (token == NULL)
		return (NULL);
	i = 0;
	while (i < token_len)
	{
		token[i] = s[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}
