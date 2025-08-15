#include "minishell.h"

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
