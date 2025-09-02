#include "minishell.h"

void	exec_cmd(t_cmd *cmd, char **envp, t_shell *shell)
{
	char	*path;

	expand_remove_quotes_cmd(cmd, shell);
	if (apply_redirections(cmd->redir, shell) < 0)
		exit(shell->last_exit_code);
	if (exec_builtin(cmd, shell))
		exit(shell->last_exit_code);
	path = get_path(cmd);
	if (!path)
	{
		printf("%s: command not found\n", cmd->commands[0]);
		shell->last_exit_code = 127;
		exit(shell->last_exit_code);
	}
	if (execve(path, cmd->commands, envp) == -1)
	{
		perror("execve failed");
		free(path);
		shell->last_exit_code = 126;
		exit(shell->last_exit_code);
	}
}
