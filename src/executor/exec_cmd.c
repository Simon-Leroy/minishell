#include "minishell.h"

void	exec_cmd(t_cmd *cmd, char **envp, t_shell *shell)
{
	char	*path;

	expand_remove_quotes_cmd(cmd, shell);
	if (apply_redirections(cmd->redir, shell) < 0)
		exit(shell->last_exit_code);
	path = get_path(cmd);
	if (execve(path, cmd->commands, envp) == -1)
	{
		perror("execve failed");
		free(path);
		shell->last_exit_code = 126;
		exit(shell->last_exit_code);
	}
}
