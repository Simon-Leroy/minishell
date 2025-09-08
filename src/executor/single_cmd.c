#include "minishell.h"

void	single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (is_parent_builtin(cmd->commands[0]))
	{
		exec_builtin(cmd, shell);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd, shell);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
		else
			shell->last_exit_code = 1;
	}
}
