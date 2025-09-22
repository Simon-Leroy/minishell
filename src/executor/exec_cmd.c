#include "minishell.h"

static void	handle_fail(t_shell *shell, char *path, int exit_code, char **envp)
{
	perror("minishell");
	shell->last_exit_code = exit_code;
	if (path)
		free(path);
	if (envp)
		ft_free_tab(envp);
	exit(exit_code);
}

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
		handle_fail(shell, path, 1, NULL);
	if (execve(path, cmd->commands, envp) == -1)
		handle_fail(shell, path, 126, envp);
	free(path);
}
