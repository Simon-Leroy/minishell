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

// Traite un token de redirection simple (INPUT, OUTPUT, APPEND, HEREDOC)
// Appelle handle_heredoc si c'est un heredoc

int	process_redir_token(t_token *tok, t_redir **redir, int *heredoc_count)
{
	if (!tok->next || tok->next->type != WORD)
	{
		perror("Syntax error");
		return (0);
	}
	if (tok->type == HEREDOC)
	{
		if (!handle_heredoc(tok, *heredoc_count))
			return (0);
		(*heredoc_count)++;
	}
	if (!append_redir(redir, tok))
		return (0);
	return (1);
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
		return (free(new_node), 0);
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
// Parcourt les tokens avant un pipe et extrait les redirections

int	extract_redir(t_token **tok, t_redir **redir)
{
	int	heredoc_count = 0;

	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type != WORD)
		{
			if (!process_redir_token(*tok, redir, &heredoc_count))
				return (0);
			*tok = (*tok)->next->next;
		}
		else
			*tok = (*tok)->next;
	}
	return (1);
}

/* int	extract_redir(t_token **tok, t_redir **redir)
{
	int		heredoc_count;
	int		fd;
	char	*tmp_filename;

	heredoc_count = 0;
	while (*tok != NULL && (*tok)->type != PIPE)
	{
		if ((*tok)->type != WORD)
		{
			if ((*tok)->next == NULL || (*tok)->next->type != WORD)
			{
				perror("Erreur de syntaxe\n");
				return (0);
			}
			if ((*tok)->next->type == HEREDOC)
			{
				fd = heredoc_fd((*tok)->next->value, heredoc_count++);
				if (fd < 0)
				{
					perror("heredoc failed");
					return (0);
				}
				tmp_filename = generate_tmp_filename(heredoc_count - 1);
				if (!tmp_filename)
					return (0);
				free((*tok)->next->value);
				(*tok)->next->value = tmp_filename;
			}
			if (!append_redir(redir, *tok, &heredoc_count))
				return (0);
			(*tok) = (*tok)->next->next;
		}
		else
			(*tok) = (*tok)->next;
	}
	return (1);
} */
