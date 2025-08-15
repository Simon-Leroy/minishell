#include "minishell.h"

int	first_command(t_cmd *cmd, char **envp, pid_t *pid_out, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
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
		exec_cmd(cmd, envp, shell);
	}
	*pid_out = pid;
	check_close(fd[1]);
	return (fd[0]);
}

int	middle_pipes(t_cmd *cmd, char **envp, int *fd, pid_t *pid_out, t_shell *shell)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		return (1);
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
		exec_cmd(cmd, envp, shell);
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

int	last_command(t_cmd *cmd, char **envp, int *fd, pid_t *pid_out, t_shell *shell)
{
	pid_t	pid;

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
		exec_cmd(cmd, envp, shell);
	}
	else
	{
		close_pipe(fd);
		*pid_out = pid;
	}
	return (0);
}

void	multiple_commands(t_cmd *cmd, char **envp, pid_t *pids, t_shell *shell)
{
	size_t	i;
	size_t	j;
	int		fd[2];
	int status;
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	fd[0] = -1;
	fd[1] = -1;
	fd[0] = first_command(tmp, envp, &pids[i++], shell);
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		middle_pipes(tmp, envp, fd, &pids[i++], shell);
		tmp = tmp->next;
	}
	if (tmp)
		last_command(tmp, envp, fd, &pids[i++], shell);
	j = 0;
	while (j < i)
	{
		waitpid(pids[j++], &status, 0);
		if ((j == i - 1) && WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
	}
	free(pids);
}
