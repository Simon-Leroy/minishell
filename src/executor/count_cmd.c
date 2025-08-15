#include "minishell.h"

size_t	get_nbr_commands(t_cmd *cmd)
{
	size_t	count;
	t_cmd	*tmp;

	tmp = cmd;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
