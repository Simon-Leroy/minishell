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
		{
			if ((s[i] == '>' || s[i] == '<') && s[i + 1] && s[i] == s[i + 1])
			{
				i++;
				words++;
			}
			else
				words++;
		}
		else if (!check_char(s[i]) && (check_char(s[i + 1]) || is_separator(s[i + 1])))
			words++;
		i++;
	}
	return (words);
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

/* int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("Longueur token : %li\n", ft_token_len(argv[1]));
	return (0);
} */

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
