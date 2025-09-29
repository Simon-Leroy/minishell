/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:16 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 12:52:20 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_parent_process(pid_t pid, int *status, t_shell *shell)
{
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(*status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
	setup_signal();
	if (WIFEXITED(*status))
		shell->last_exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		shell->last_exit_code = 128 + WTERMSIG(*status);
	else
		shell->last_exit_code = 1;
}

/*
Fonction d'exécution d'une commande seule

1) On commence par ignorer les signaux dans le processus parent
pour ne pas qu'il soit interrompu par Ctrl + C
2) On fork et on rétablit les signaux dans le processus enfant
pour que le processus puisse être interrompu
3) On exécute la commande
4) On récupère le code de sortie dans le processus parent
*/
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
