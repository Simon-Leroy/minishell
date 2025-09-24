/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:15 by roguille          #+#    #+#             */
/*   Updated: 2025/09/25 00:05:48 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_redirections(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (redir->type == INPUT || redir->type == HEREDOC)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == OUTPUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (exit_errno(shell), perror(redir->filename), -1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

static void	run_multiple_or_single(t_cmd *cmd, t_shell *shell, size_t nbr)
{
	pid_t	*pids;

	if (nbr == 1)
	{
		if (is_parent_builtin(cmd->commands[0]))
		{
			expand_remove_quotes_cmd(cmd, shell);
			shell->last_exit_code = exec_builtin(cmd, shell);
		}
		else
			single_command(cmd, shell);
	}
	else if (nbr > 1)
	{
		pids = malloc(sizeof(pid_t) * nbr);
		if (!pids)
		{
			perror("malloc error");
			shell->last_exit_code = 1;
			return ;
		}
		multiple_commands(cmd, pids, shell);
	}
}

// Traitement des redirections seules "> out" ou "> in" sans rien d'autre
static int	run_empty_command(t_cmd *cmd, t_shell *shell, size_t nbr)
{
	if (nbr == 1 && (!cmd->commands || !cmd->commands[0]))
	{
		expand_remove_quotes_cmd(cmd, shell);
		if (validate_redirections(cmd->redir, shell) < 0)
			shell->last_exit_code = 1;
		else
			shell->last_exit_code = 0;
		return (1);
	}
	return (0);
}

void	run_commands(t_cmd *cmd, t_shell *shell)
{
	size_t	nbr_commands;

	if (!cmd)
	{
		shell->last_exit_code = 2;
		return ;
	}
	nbr_commands = get_nbr_commands(cmd);
	if (run_empty_command(cmd, shell, nbr_commands))
		return ;
	run_multiple_or_single(cmd, shell, nbr_commands);
}
