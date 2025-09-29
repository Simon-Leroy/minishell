/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:11 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 12:55:22 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_and_builtin(t_cmd *cmd, t_shell *shell)
{
	if (is_parent_builtin(cmd->commands[0]))
		exit(exec_builtin(cmd, shell));
	else
		exec_cmd(cmd, shell);
}
/*
L’entrée vient de STDIN, la sortie va vers le pipe suivant
-> uniquement besoin de redigirer la sortie vers l’écriture
-> dup2(fd[1], STDOUT)

Fermetures dans l’enfant :
-on utilise pas fd[0] car l’entrée vient du terminal
-> on le ferme immédiatement
-après dup2 on peut fermer fd[1] car STDOUT pointe déjà dessus

Fermetures dans le parent :
-on ferme fd[1] sinon le pipe ne sera pas considéré comme vide et
la commande suivante ne pourra pas lire fd[0]

On return fd[0] qui est passé à la commande suivante en argument
*/
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

static void	child_middle_pipe(t_cmd *cmd, int *fd, int *fd_pipe, t_shell *shell)
{
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd_pipe[1], 1) < 0)
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
		child_middle_pipe(cmd, fd, fd_pipe, shell);
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
