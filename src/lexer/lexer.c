#include "minishell.h"

// Split la string en tokens puis forme une liste chaînée
// avec tous les tokens produits -> 1 noeud = 1 token
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
