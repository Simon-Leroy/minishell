#include "minishell.h"

void	run_commands(t_cmd *cmd, char **envp, t_shell *shell)
{
	size_t	nbr_commands;
	pid_t	*pids;

	nbr_commands = get_nbr_commands(cmd);
	if (nbr_commands == 1)
	{
		single_command(cmd, envp, shell);
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
		multiple_commands(cmd, envp, pids, shell);
	}
}
