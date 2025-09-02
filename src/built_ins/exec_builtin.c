#include "minishell.h"

int is_parent_builtin(char *name)
{
	return (!ft_strcmp(name, "exit"));
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->commands[0];
	if (ft_strcmp(name, "exit") == 0)
	{
		return (ft_exit(cmd->commands, shell->last_exit_code));
	}
	return (0);
}
