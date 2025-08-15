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
