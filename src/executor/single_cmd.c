/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:16 by roguille          #+#    #+#             */
/*   Updated: 2025/09/24 16:33:04 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_parent_process(pid_t pid, int *status, t_shell *shell)
{
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		write(1, "\n", 1);
	setup_signal();
	if (WIFEXITED(*status))
		shell->last_exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		shell->last_exit_code = 128 + WTERMSIG(*status);
	else
		shell->last_exit_code = 1;
}

void	single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	ignore_signal();
	pid = fork();
	if (pid == 0)
	{
		restore_signal();
		exec_cmd(cmd, shell);
	}
	else
		single_parent_process(pid, &status, shell);
}
