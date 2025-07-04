#include "minishell.h"

// Retourne un pointeur sur le dernier noeud de la liste t_redir
// renvoie NULL si la liste est vide
t_redir	*ft_lst_last_redir(t_redir *list)
{
	t_redir	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// Ajoute une redirection à la fin de la liste *head en se basant sur
// le token tok et son WORD suivant (nom de fichier).
// - Crée un nouveau noeud `t_redir`
// - Duplique le nom de fichier avec `ft_strdup`
// - Marque les deux tokens comme étant des redirections avec is_redir = 1
// Retourne 1 en cas de succès, 0 si erreur d’allocation ou de syntaxe.

int	append_redir(t_redir **head, t_token *tok)
{
	t_redir	*new_node;
	t_redir	*last;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (0);
	if (!tok->next || tok->next->type != WORD)
		return (0);
	new_node->type = tok->type;
	new_node->filename = ft_strdup(tok->next->value);
	if (!new_node->filename)
		return (free(new_node), 0);
	new_node->next = NULL;
	tok->is_redir = 1;
	tok->next->is_redir = 1;
	if (!*head)
		*head = new_node;
	else
	{
		last = ft_lst_last_redir(*head);
		last->next = new_node;
	}
	return (1);
}
// Parcourt les tokens d'un bloc (avant un pipe ou la fin de la liste)
// et extrait toutes les redirections pour les mettre dans redir
// Renvoie 0 en cas d'erreur de syntaxe (symbole de redirection pas suivi par un nom de fichier)
int	extract_redir(t_token **tok, t_redir **redir)
{
	while (*tok != NULL && (*tok)->type != PIPE)
	{
		if ((*tok)->type != WORD)
		{
			if ((*tok)->next == NULL || (*tok)->next->type != WORD)
			{
				perror("Erreur de syntaxe\n");
				return (0);
			}
			append_redir(redir, *tok);
			(*tok) = (*tok)->next->next;
		}
		else
			(*tok) = (*tok)->next;
	}
	return (1);
}

int main(void)
{
	char *test = "bonjour grep < infile | cat >> test.txt";

	t_token *tokens;
	t_cmd	*cmd;
	t_cmd	*tmp;

	tokens = list_tokens(test);
	cmd = link_cmd_redir(tokens);
 	tmp = cmd;
	while (tmp)
	{
		printf("Command:\n");
		for (int i = 0; tmp->commands[i]; i++)
			printf("  - %s\n", tmp->commands[i]);
		t_redir *r = tmp->redir;
		while (r)
		{
			printf("  Redirection: type %d → %s\n", r->type, r->filename);
			r = r->next;
		}
		tmp = tmp->next;
	}
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
}
