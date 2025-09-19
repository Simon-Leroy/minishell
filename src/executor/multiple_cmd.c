#include "minishell.h"

static void	exec_cmd_and_builtin(t_cmd *cmd, t_shell *shell)
{
	if (is_parent_builtin(cmd->commands[0]))
		exit(exec_builtin(cmd, shell));
	else
		exec_cmd(cmd, shell);
}

int	first_command(t_cmd *cmd, pid_t *pid_out, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	ignore_signal();
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		check_close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			close_pipe(fd);
			exit(EXIT_FAILURE);
		}
		check_close(fd[1]);
		restore_signal();
		exec_cmd_and_builtin(cmd, shell);
	}
	*pid_out = pid;
	check_close(fd[1]);
	return (fd[0]);
}

int	middle_pipes(t_cmd *cmd, int *fd, pid_t *pid_out, t_shell *shell)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		return (1);
	ignore_signal();
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd_pipe[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close_pipe(fd);
			close_pipe(fd_pipe);
			exit(EXIT_FAILURE);
		}
		close_pipe(fd);
		close_pipe(fd_pipe);
		restore_signal();
		exec_cmd_and_builtin(cmd, shell);
	}
	else
	{
		close_pipe(fd);
		check_close(fd_pipe[1]);
		fd[0] = fd_pipe[0];
		*pid_out = pid;
	}
	return (0);
}

int	last_command(t_cmd *cmd, int *fd, pid_t *pid_out, t_shell *shell)
{
	pid_t	pid;

	ignore_signal();
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		check_close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 failed");
			close_pipe(fd);
			exit(EXIT_FAILURE);
		}
		check_close(fd[0]);
		restore_signal();
		exec_cmd_and_builtin(cmd, shell);
	}
	else
	{
		close_pipe(fd);
		*pid_out = pid;
	}
	return (0);
}

static void	wait_for_children(pid_t *pids, size_t n, t_shell *shell)
{
	size_t	j;
	int		status;

	j = 0;
	while (j < n)
	{
		waitpid(pids[j], &status, 0);
		if (j == n - 1)
		{
			if (WIFEXITED(status))
				shell->last_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				shell->last_exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
			}
		}
		j++;
	}
}

void	multiple_commands(t_cmd *cmd, pid_t *pids, t_shell *shell)
{
	size_t	i;
	int		fd[2];
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	fd[0] = -1;
	fd[1] = -1;
	ignore_signal();
	fd[0] = first_command(tmp, &pids[i++], shell);
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		middle_pipes(tmp, fd, &pids[i++], shell);
		tmp = tmp->next;
	}
	if (tmp)
		last_command(tmp, fd, &pids[i++], shell);
	wait_for_children(pids, i, shell);
	setup_signal();
	free(pids);
}
