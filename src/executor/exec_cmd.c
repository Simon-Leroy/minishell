#include "minishell.h"

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;
	int		ret;

	expand_remove_quotes_cmd(cmd, shell);
	if (!cmd->commands[0] || cmd->commands[0][0] == '\0')
	{
		shell->last_exit_code = 0;
		return ;
	}
	if (apply_redirections(cmd->redir, shell) < 0)
		exit(1);
	ret = exec_builtin(cmd, shell);
	if (ret != -1)
		exit(ret);
	path = get_path(cmd, shell->env);
	check_path(cmd->commands[0], path, shell);
	envp = build_envp(shell->env);
	if (!envp)
	{
		perror("env build failed");
		shell->last_exit_code = 1;
		free(path);
		exit(shell->last_exit_code);
	}
	if (execve(path, cmd->commands, envp) == -1)
	{
		perror("execve failed");
		free(path);
		shell->last_exit_code = 126;
		exit(shell->last_exit_code);
	}
	free(path);
}
