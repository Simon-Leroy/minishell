#include "minishell.h"

// Détermine si le caractère est un white space ou une fin de chaîne
int	check_char(char c)
{
	if ((c >= 9 && c <= 12) || c == ' ' || c == '\0')
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
		// Lorsqu'un single/double quote est rencontré, tout ce qui est
		// à l'intérieur des quotes est skip puis si le caractère après
		// le quote est un white space -> +1 token
		if (s[i] == '\'')
		{
			validate_quote_closure(s, '\'', &i);
			if (check_char(s[i + 1]))
				words++;
		}
		else if (s[i] == '\"')
		{
			validate_quote_closure(s, '\"', &i);
			if (check_char(s[i + 1]))
				words++;
		}
		else if (!check_char(s[i]) && check_char(s[i + 1]))
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
size_t	ft_token_len(char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (check_char(str[i]))
			break ;
		if (str[i] == '\'')
			increment_len(str, &i, &len, '\'');
		else if (str[i] == '\"')
			increment_len(str, &i, &len, '\"');
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

static void	free_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

// Découpe la string s en un tableau de tokens en tenant compte des quotes
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
/*
int main()
{
	char *str = "";
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
