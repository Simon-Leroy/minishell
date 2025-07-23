#include "minishell.h"

char	*get_path(t_cmd *cmd)
{
	char	*path;

	if (!cmd->commands[0])
	{
//		ft_free_tab(cmd->commands);
		perror("could not find command");
		exit(127);
	}
	path = path_handler(cmd->commands[0]);
	if (!path)
	{
//		ft_free_tab(args);
		perror("could not find command");
		exit(127);
	}
	return (path);
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	if (apply_redirections(cmd->redir) < 0)
		exit(1);
	path = get_path(cmd);
	if (execve(path, cmd->commands, envp) == -1)
	{
		perror("execve failed");
		free(path);
		exit(126);
	}
}

size_t	get_nbr_commands(t_cmd *cmd)
{
	size_t	count;
	t_cmd	*tmp;

	tmp = cmd;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	single_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_cmd(cmd, envp);
	else
		waitpid(pid, NULL, 0);
}

void	multiple_commands(t_cmd *cmd, char **envp, pid_t *pids)
{
	size_t	i;
	size_t	j;
	int		fd;
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	fd = first_command(tmp, envp, &pids[i++]);
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		middle_pipes(tmp, envp, &fd, &pids[i++]);
		tmp = tmp->next;
	}
	if (tmp)
		last_command(tmp, envp, &fd, &pids[i++]);
	j = 0;
	while (j < i)
		waitpid(pids[j++], NULL, 0);
	free(pids);
}

void	run_commands(t_cmd *cmd, char **envp)
{
	size_t	nbr_commands;
	pid_t	*pids;

	nbr_commands = get_nbr_commands(cmd);
	if (nbr_commands == 1)
	{
		single_command(cmd, envp);
	}
	else if (nbr_commands > 1)
	{
		pids = malloc(sizeof(pid_t) * nbr_commands);
		if (!pids)
			return ;
		multiple_commands(cmd, envp, pids);
	}
}
