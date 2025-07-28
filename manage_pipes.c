#include "minishell.h"

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

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
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			close_pipe(fd);
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		exec_cmd(cmd, envp, shell);
	}
	*pid_out = pid;
	close(fd[1]);
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
		close(fd_pipe[1]);
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
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 failed");
			close_pipe(fd);
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		exec_cmd(cmd, envp, shell);
	}
	else
	{
		close_pipe(fd);
		*pid_out = pid;
	}
	return (0);
}
