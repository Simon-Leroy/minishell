#include "minishell.h"

void	run_commands(t_cmd *cmd, t_shell *shell)
{
	size_t	nbr_commands;
	pid_t	*pids;

	nbr_commands = get_nbr_commands(cmd);
	if (nbr_commands == 1)
	{
		if (is_parent_builtin(cmd->commands[0]))
			shell->last_exit_code = exec_builtin(cmd, shell);
		else
			single_command(cmd, shell);
	}
	else if (nbr_commands > 1)
	{
		pids = malloc(sizeof(pid_t) * nbr_commands);
		if (!pids)
		{
			perror("malloc error");
			shell->last_exit_code = 1;
			return ;
		}
		multiple_commands(cmd, pids, shell);
	}
}
