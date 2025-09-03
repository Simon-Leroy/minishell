#include "minishell.h"

void	exec_cmd(t_cmd *cmd, char **envp, t_shell *shell)
{
	char	*path;

	expand_remove_quotes_cmd(cmd, shell);
	if (!cmd->commands[0] || cmd->commands[0][0] == '\0')
	{
		shell->last_exit_code = 0;
		exit(0);
	}
	if (apply_redirections(cmd->redir, shell) < 0)
	{
		shell->last_exit_code = 1;
		exit(shell->last_exit_code);
	}
	if (exec_builtin(cmd, shell))
		exit(shell->last_exit_code);
	path = get_path(cmd);
	if (!path)
	{
		print_error(cmd->commands[0], 127);
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
