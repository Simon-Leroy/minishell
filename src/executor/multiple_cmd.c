/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:09 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:10 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
