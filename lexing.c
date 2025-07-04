#include "minishell.h"

// Assigne un type en fonction des caractères spéciaux rencontrés
t_token_type get_t_type(char *str)
{
	t_token_type	type;

	if (ft_strncmp(str, "|", 1) == 0)
		type = PIPE;
	else if (ft_strncmp(str, "<<", 2) == 0)
		type = HEREDOC;
	else if (ft_strncmp(str, ">>", 2) == 0)
		type = APPEND;
	else if (ft_strncmp(str, ">", 1) == 0)
		type = OUTPUT;
	else if (ft_strncmp(str, "<", 1) == 0)
		type = INPUT;
	else
		type = WORD;
	return (type);
}

// Renvoie un pointeur vers le dernier noeud de la liste chaînée de tokens
t_token	*ft_lst_last_token(t_token *list)
{
	t_token	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// Ajoute un nouveau token à la liste chaînée et crée le premier noeud
// si la liste est vide
int	append_token(t_token **list, char *value, t_token_type type)
{
	t_token	*new_node;
	t_token	*last;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (0);
	new_node->value = strdup(value);
	new_node->type = type;
	new_node->is_redir = 0;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		last = ft_lst_last_token(*list);
		last->next = new_node;
	}
	return (1);
}

// Split la string en tokens puis forme une liste chaînée
// avec tous les tokens produits -> 1 noeud = 1 token
t_token	*list_tokens(char *str)
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
	return (list);
}

/* void	print_type(int type)
{
	if (type == 0)
		printf("Type : PIPE\n");
	else if (type == 1)
		printf("Type : WORD\n");
	else if (type == 2)
		printf("Type : INPUT\n");
	else if (type == 3)
		printf("Type : OUTPUT\n");
	else if (type == 4)
		printf("Type : APPEND\n");
	else if (type == 5)
		printf("Type : HEREDOC\n");
} */
